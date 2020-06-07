//Basé sur le code serveur du TP 7

#include "pse.h"

#define    CMD      "serveur"
#define nb_threads 10

//Initialisation des variables globales et fonctions utilisées dans les différents threads ainsi que du journal
void *worker(void *arg);
void sessionClient(int canal);
void remiseAZeroJournal(void);
void *retour_client(void *arg);

int fdJournal;
DataSpec workers[nb_threads];
DataSpec workers_ret[nb_threads];
char ligne_globale[LIGNE_MAX];

char client_names[nb_threads][20];
int client_votes[nb_threads];



int main(int argc, char *argv[]) {

  //Initialisation des variables et du journal
  short port;
  int ecoute, canal, ret;
  struct sockaddr_in adrEcoute, adrClient;
  unsigned int lgAdrClient;

  for(int i = 0;i<nb_threads;i++)
	strcpy(client_names[i],"/");
  for(int i = 0;i<nb_threads;i++)
	client_votes[i] = 0;

  fdJournal = open("journal.log", O_WRONLY|O_CREAT|O_APPEND, 0644);
  if (fdJournal == -1)
    erreur_IO("ouverture journal");

  if (argc != 2)
    erreur("usage: %s port\n", argv[0]);

  //création des threads
  for(int i = 0; i <nb_threads; i++)
  {
	workers[i].canal = -1;
	sem_init(&workers[i].sem, 0, 0);
	sem_init(&workers_ret[i].sem, 0, 0);
	workers[i].tid = i;
	pthread_create(&workers[i].id, NULL, worker, &workers[i].tid);
  }

  //Initialisation de la connexion
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

  initDataThread();
  while (VRAI) {

	//Connexion aux clients et attente de la libération d'un thread le cas échéant
    printf("%s: accepting a connection\n", CMD);
    canal = accept(ecoute, (struct sockaddr *)&adrClient, &lgAdrClient);
    if (canal < 0)
      erreur_IO("accept");

    printf("%s: adr %s, port %hu\n", CMD,
	      stringIP(ntohl(adrClient.sin_addr.s_addr)), ntohs(adrClient.sin_port));

	int libre = -1;
	while(libre == -1)
	{
			for(int i = 0; i<nb_threads; i++)
				if(workers[i].canal == -1)
				{
					libre = i;
					break;
				}
			usleep(100000);
	}
	workers[libre].canal = canal;
	sem_post(&workers[libre].sem);

  }

  if (close(ecoute) == -1)
    erreur_IO("fermeture ecoute");

  if (close(fdJournal) == -1)
    erreur_IO("fermeture journal");

  libererDataThread();
  exit(EXIT_SUCCESS);
}

//Fonction de chaque thread avec attente de la libération du thread pour effectuer la fonction client
void *worker(void *arg) {
	int *tid = (int*)arg;
	while(1)
	{
		sem_wait(&workers[*tid].sem);
		sem_init(&workers_ret[*tid].sem, 0, 0);
		pthread_create(&workers_ret[*tid].id, NULL, retour_client, tid);
		sessionClient(workers[*tid].canal);
		workers[*tid].canal = -1;
		workers_ret[*tid].canal = -1;
	}
	pthread_exit(NULL);
}

//Fonction client transmettant les messages entre les clients et effectuant les différentes commandes
void sessionClient(int canal) {
  int fin = FAUX;
  char ligne[LIGNE_MAX];
  char ligne2[LIGNE_MAX];
  int lgLue;
  char nom[20];

  //Initialisation du nom du client
  lgLue = lireLigne(canal, ligne);
    if (lgLue < 0)
      erreur_IO("lireLigne");
    else if (lgLue == 0)
      erreur("interruption client\n");
	strncpy(nom,ligne,20);

	for(int i = 0;i<2*nb_threads;i++){
		if(strcmp(client_names[i%nb_threads],nom) == 0)
			break;
		if(strcmp(client_names[i%nb_threads],"/") == 0 && i >= nb_threads){
			strcpy(client_names[i%nb_threads],nom);
			break;
		}
	}
	printf("%s s'est connecté au serveur\n", nom);

  //Boucle de communication
  while (!fin) {
    lgLue = lireLigne(canal, ligne);
    if (lgLue < 0)
      erreur_IO("lireLigne");
    else if (lgLue == 0)
      erreur("interruption client\n");

    //Commande d'arrêt du client
    if (strcmp(ligne, "/fin") == 0) {
        fin = VRAI;
    }

	//Commande de remise a zéro du journal et des votes
    else if (strcmp(ligne, "/clear") == 0) {
      printf("%s: remise a zero journal et des votes\n", CMD);
      remiseAZeroJournal();
	  for(int i = 0;i<nb_threads;i++){
			client_votes[i] = 0;
		}
    }

	//Commande envoyant le nombre de vote de chaque client aux clients
	else if (strcmp(ligne, "/votecount") == 0) {
		for(int i = 0;i<nb_threads;i++){
			if(strcmp(client_names[i],"/") != 0){
				sprintf(ligne_globale,"%d votes contre %s\n",client_votes[i],client_names[i]);
				for(int j = 0; j <nb_threads; j++)
				{
					sem_post(&workers_ret[j].sem);
				}
			}
		}
    }

	//Commande ajoutant un vote contre un client
	else if (strcmp(ligne, "/vote") == 0) {

	lgLue = lireLigne(canal, ligne);
    if (lgLue < 0)
      erreur_IO("lireLigne");
    else if (lgLue == 0)
      erreur("interruption client\n");

    for(int i = 0;i<nb_threads;i++){
		if(strcmp(client_names[i],ligne) == 0)
			client_votes[i]++;
	}

	strcpy(ligne2,nom);
	strcat(ligne2," a voté contre ");
	strncat(ligne2,ligne,LIGNE_MAX);
	strcpy(ligne_globale,ligne2);
    for(int i = 0; i <nb_threads; i++)
		{
			if(workers[i].canal != canal)
				sem_post(&workers_ret[i].sem);
		}
    }
	else{
		strcpy(ligne2,nom);
		strcat(ligne2," > ");
		strncat(ligne2,ligne,LIGNE_MAX);
		strcpy(ligne_globale,ligne2);
		for(int i = 0; i <nb_threads; i++)
		{
			if(workers[i].canal != canal)
				sem_post(&workers_ret[i].sem);
		}
		if (ecrireLigne(fdJournal, ligne_globale) != -1) {
			printf("%s: ligne de %d octets ecrite dans journal\n", CMD, lgLue);
		}
		else
			erreur_IO("ecriture journal");
	}

  }

  //Déconnexion du client et réinitialisation des variables correspondant
  printf("%s s'est déconnecté du serveur\n", nom);
  sprintf(ligne_globale,"%s s'est déconnecté du serveur\n", nom);
  for(int i = 0; i <nb_threads; i++)
		{
			if(workers[i].canal != canal)
				sem_post(&workers_ret[i].sem);
		}
  for(int i = 0;i<nb_threads;i++){
		if(strcmp(client_names[i],nom) == 0){
			strcpy(client_names[i],"/");
			client_votes[i] = 0;
		}
  }

  if (close(canal) == -1)
    erreur_IO("fermeture canal");
}

//Fonction de remise à zéro du journal
void remiseAZeroJournal(void) {
  if (close(fdJournal) == -1)
    erreur_IO("raz journal - fermeture");

  fdJournal = open("journal.log", O_WRONLY|O_TRUNC|O_APPEND, 0644);
  if (fdJournal == -1)
    erreur_IO("raz journal - ouverture");
}

//Fonction de chaque thread secondaire servant a communiquer les messages aux clients (de la part du serveur ou d'autres clients)
void *retour_client(void *arg) {
	int *tid = (int*)arg;
	int lgEcr;
	while(1)
	{
		sem_wait(&workers_ret[*tid].sem);
	    lgEcr = ecrireLigne(workers[*tid].canal, ligne_globale);
		if (lgEcr == -1)
		{
			close(workers_ret[*tid].canal);
			pthread_exit(NULL);
		}
	}
	pthread_exit(NULL);
}
