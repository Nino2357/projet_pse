//Basé sur le code client du TP 7

#include "pse.h"

#define CMD   "client"

//Fonction de lecture des donnés envoyées par le serveur en retour au client
void *retour_serv(void *arg);

//Thread destiné a effectuer cette fonction de retour
DataSpec thread_retour;

int main(int argc, char *argv[]) {
	
  //Initialisation des variables de la fonction client
  int sock, ret;
  struct sockaddr_in *adrServ;
  int fin = FAUX;
  char ligne[LIGNE_MAX];
  int lgEcr;
  char nom[20];


  //Message d'erreur de mauvaise utilisation du client
  if (argc != 3)
    erreur("usage: %s machine port\n", argv[0]);

  printf("%s: creating a socket\n", CMD);
  sock = socket (AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    erreur_IO("socket");

  printf("%s: DNS resolving for %s, port %s\n", CMD, argv[1], argv[2]);
  adrServ = resolv(argv[1], argv[2]);
  if (adrServ == NULL)
    erreur("adresse %s port %s inconnus\n", argv[1], argv[2]);

  printf("%s: adr %s, port %hu\n", CMD,
	        stringIP(ntohl(adrServ->sin_addr.s_addr)),
	        ntohs(adrServ->sin_port));

  printf("%s: connecting the socket\n", CMD);
  ret = connect(sock, (struct sockaddr *)adrServ, sizeof(struct sockaddr_in));
  if (ret < 0)
    erreur_IO("connect");

	printf("\nEntrez un nom : ");
	scanf("%s", nom);
	lgEcr = ecrireLigne(sock, nom);
	pthread_create(&thread_retour.id, NULL, retour_serv, &sock);

  //On entre en boucle infinie du texte a envoyer au serveur
  while (!fin) {
    if (fgets(ligne, LIGNE_MAX, stdin) == NULL)
      erreur("saisie fin de fichier\n");

    lgEcr = ecrireLigne(sock, ligne);
    if (lgEcr == -1)
      erreur_IO("ecrire ligne");

    //Commande pour voter contre un autre client
	if (strcmp(ligne, "/vote\n") == 0){
		printf("\nEntrez le nom de la cible de votre vote : ");
		
	if (fgets(ligne, LIGNE_MAX, stdin) == NULL)
      erreur("saisie fin de fichier\n");

    lgEcr = ecrireLigne(sock, ligne);
    if (lgEcr == -1)
      erreur_IO("ecrire ligne");
	}

    //Commande d'arrêt du client
    if (strcmp(ligne, "/fin\n") == 0)
      fin = VRAI;
  }

  if (close(sock) == -1)
    erreur_IO("close socket");

  exit(EXIT_SUCCESS);
}

void *retour_serv(void *arg) {
	
	//Initialisation des variables de la fonction de retour et récupération du canal
	short *sock = (short*)arg;
	int lgLue;
	char ligne[LIGNE_MAX];
	
	//On lit en boucle infinie le texte envoyé par le serveur
	while(1)
	{
	lgLue = lireLigne(*sock, ligne);
    if (lgLue < 0)
      erreur_IO("lireLigne");
    else if (lgLue == 0)
      erreur("interruption client\n");

    printf("%s\n", ligne);
	}
	pthread_exit(NULL);
}
