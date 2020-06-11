#include "serveur.h"

void creerCohorteWorkers(void);
int chercherWorkerLibre(void);
void *threadWorker(void *arg);
void sessionClient(int canal);
int ecrireJournal(char *buffer);
void remiseAZeroJournal(void);
void lockMutexJournal(void);
void unlockMutexJournal(void);
void lockMutexCanal(int numWorker);
void unlockMutexCanal(int numWorker);
void envoi(char *msg,int ecoute);

int fdJournal;
DataSpec dataSpec[NB_WORKERS];
sem_t semWorkersLibres;

// la remise a zero du journal modifie le descripteur du fichier, il faut donc
// proteger par un mutex l'ecriture dans le journal et la remise a zero
pthread_mutex_t mutexJournal;

// pour l'acces au canal d'un worker peuvant etre en concurrence la recherche
// d'un worker libre et la mise à -1 du canal par le worker
pthread_mutex_t mutexCanal[NB_WORKERS];

int main(int argc, char *argv[]) {
  short port;
  int ecoute, canal, ret;
  struct sockaddr_in adrEcoute, adrClient;
  unsigned int lgAdrClient;
  int numWorkerLibre;
  
  fdJournal = open("journal.log", O_WRONLY|O_CREAT|O_APPEND, 0644);
  if (fdJournal == -1)
    erreur_IO("ouverture journal");

  creerCohorteWorkers();

  ret = sem_init(&semWorkersLibres, 0, NB_WORKERS);
  if (ret == -1)
    erreur_IO("init sem workers libres");

  if (argc != 2)
    erreur("usage: %s port\n", argv[0]);

  port = (short)atoi(argv[1]);

  printf("%s: creating a socket\n", CMD);
  ecoute = socket (AF_INET, SOCK_STREAM, 0);
  if (ecoute < 0)
    erreur_IO("socket");
  
  adrEcoute.sin_family = AF_INET;
  adrEcoute.sin_addr.s_addr = INADDR_ANY;
  adrEcoute.sin_port = htons(port);
  printf("%s: binding to INADDR_ANY address on port %d\n", CMD, port);
  ret = bind (ecoute,  (struct sockaddr *)&adrEcoute, sizeof(adrEcoute));
  if (ret < 0)
    erreur_IO("bind");
  
  printf("%s: listening to socket\n", CMD);
  ret = listen (ecoute, 5);
  if (ret < 0)
    erreur_IO("listen");
  
  while (VRAI) {
    printf("%s: accepting a connection\n", CMD);
    canal = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
    if (canal < 0)
      erreur_IO("accept");

    printf("%s: adr %s, port %hu\n", CMD,
	      stringIP(ntohl(adrClient.sin_addr.s_addr)), ntohs(adrClient.sin_port));

    ret = sem_wait(&semWorkersLibres);  // attente d'un worker libre
    if (ret == -1)
      erreur_IO("wait sem workers libres");
    numWorkerLibre = chercherWorkerLibre();

    dataSpec[numWorkerLibre].canal = canal;
    sem_post(&dataSpec[numWorkerLibre].sem);  // reveil du worker
    if (ret == -1)
      erreur_IO("post sem worker");
  }

  if (close(ecoute) == -1)
    erreur_IO("fermeture ecoute");

  if (close(fdJournal) == -1)
    erreur_IO("fermeture journal");

  exit(EXIT_SUCCESS);
}
void envoi(char *msg,int ecoute)
{
    send(ecoute,msg,sizeof(msg),0);
    printf("%d",ecoute);
}
void creerCohorteWorkers(void) {
  int i, ret;

  for (i= 0; i < NB_WORKERS; i++) {
    dataSpec[i].canal = -1;
    dataSpec[i].tid = i;
    ret = sem_init(&dataSpec[i].sem, 0, 0);
    if (ret == -1)
      erreur_IO("init sem worker");

    ret = pthread_create(&dataSpec[i].id, NULL, threadWorker, &dataSpec[i]);
    if (ret != 0)
      erreur_IO("creation thread");
  }
}

// retourne le no. du worker libre trouve ou -1 si pas de worker libre
int chercherWorkerLibre(void) {
  int numWorkerLibre = -1, i = 0, canal;

  while (numWorkerLibre < 0 && i < NB_WORKERS) {
    lockMutexCanal(i);
    canal = dataSpec[i].canal;
    unlockMutexCanal(i);

    if (canal == -1)
      numWorkerLibre = i;
    else
      i++;
  }

  return numWorkerLibre;
}

void *threadWorker(void *arg) {
  DataSpec *dataTh = (DataSpec *)arg;
  int ret;

  while (VRAI) {
    ret = sem_wait(&dataTh->sem); // attente reveil par le thread principal
    if (ret == -1)
      erreur_IO("wait sem worker");

    printf("%s: worker %d reveil\n", CMD, dataTh->tid);

    sessionClient(dataTh->canal);

    lockMutexCanal(dataTh->tid);
    dataTh->canal = -1;
    unlockMutexCanal(dataTh->tid);

    ret = sem_post(&semWorkersLibres);  // incrementer le nb de workers libres
    if (ret == -1)
      erreur_IO("post sem workers libres");

    printf("%s: worker %d sommeil\n", CMD, dataTh->tid);
  }

  pthread_exit(NULL);
}

void sessionClient(int canal) {
  int fin = FAUX;
  char ligne[LIGNE_MAX];
  int lgLue;

  while (!fin) {
    lgLue = lireLigne(canal, ligne);
    if (lgLue < 0)
      erreur_IO("lireLigne");
    else if (lgLue == 0)
      erreur("interruption client\n");

    printf("%s: reception %d octets : \"%s\"\n", CMD, lgLue, ligne);

    if (strcmp(ligne, "fin") == 0) {
        printf("%s: fin client\n", CMD);
        fin = VRAI;
    }
    else if (strcmp(ligne, "init") == 0) {
      printf("%s: remise a zero journal\n", CMD);
      remiseAZeroJournal();
    }
    else if (ecrireJournal(ligne) != -1) {
        printf("%s: ligne de %d octets ecrite dans journal\n", CMD, lgLue);
    }
    else
      erreur_IO("ecriture journal");
  } // fin while

  if (close(canal) == -1)
    erreur_IO("fermeture canal");
}

int ecrireJournal(char *buffer)
{
  int lgLue;

  lockMutexJournal();
  lgLue = ecrireLigne(fdJournal, buffer);
  unlockMutexJournal();
  return lgLue;
}

// le fichier est ferme et rouvert vide
void remiseAZeroJournal(void) {
  lockMutexJournal();

  if (close(fdJournal) == -1)
    erreur_IO("raz journal - fermeture");

  fdJournal = open("journal.log", O_WRONLY|O_TRUNC|O_APPEND, 0644);
  if (fdJournal == -1)
    erreur_IO("raz journal - ouverture");

  unlockMutexJournal();
}

void lockMutexJournal(void)
{
  int ret;

  ret = pthread_mutex_lock(&mutexJournal);
  if (ret != 0)
    erreur_IO("lock mutex journal");
}

void unlockMutexJournal(void)
{
  int ret;

  ret = pthread_mutex_unlock(&mutexJournal);
  if (ret != 0)
    erreur_IO("lock mutex journal");
}

void lockMutexCanal(int numWorker)
{
  int ret;

  ret = pthread_mutex_lock(&mutexCanal[numWorker]);
  if (ret != 0)
    erreur_IO("lock mutex dataspec");
}

void unlockMutexCanal(int numWorker)
{
  int ret;

  ret = pthread_mutex_unlock(&mutexCanal[numWorker]);
  if (ret != 0)
    erreur_IO("lock mutex dataspec");
}
