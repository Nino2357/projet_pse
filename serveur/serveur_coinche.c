#include "serveur_coinche.h"

int main(int argc, char *argv[])
{
    partie();
    return 0;
}

void partie(void)
{
    
    player p0, p1, p2, p3; //Création des joueurs
    team team0, team1; //Création des equipes
    //Initalisation
    p0.id = 0;
    p1.id = 1;
    p2.id = 2;
    p3.id = 3;
    team0.p0= p0;
    team0.p1= p2;
    team1.p0= p1;
    team1.p1= p3;
    team0.id = 0;
    team1.id = 1;
    player liste_joueur[4]={p0,p1,p2,p3};
    init_serveur(liste_joueur);
}

void init_serveur(player *liste_joueur) //Initialise le serveur et prend les adresses des clients
{
    //Création du serveur
    struct sockaddr_in addr_serv; //adresse du serveur
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(3005);
    addr_serv.sin_addr.s_addr = INADDR_ANY;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if ( sockfd == -1 ) 
    {
        perror ("socket" );
        exit ( EXIT_FAILURE );
    }
    if (bind(sockfd, (struct sockaddr *) &addr_serv, sizeof(addr_serv))!=0)
    {
        perror ( "bind" );
        exit ( EXIT_FAILURE );   
    }
    if ( listen ( sockfd, 4 ) != 0 ) 
    {
        perror ( "listen" );
        exit ( EXIT_FAILURE );
    }
    //Récuperation des clients 
    struct sockaddr_in addr_cli[4]; //adresse des clients
    int sockconn[4];
    char name[10];
    char msg[100];
    unsigned int lg_addr_cli;
    for(int cli=0; cli<4; cli++)
    {
        addr_cli[cli].sin_family = AF_INET;
        addr_cli[cli].sin_port = htons(3005);
        addr_cli[cli].sin_addr.s_addr = INADDR_ANY;
        sockconn[cli] = accept ( sockfd, (struct sockaddr *) &addr_cli[cli], &lg_addr_cli);
        if ( sockconn[cli] == -1 ) 
        { 
            perror ( "accept" ); 
            exit ( EXIT_FAILURE ); 
        }
        sprintf(msg,"Bienvenue_joueur p%d \nVeillez entrez votre nom svp :\n",cli);
        liste_joueur[cli].sockid = sockconn[cli];
        printf("%d, %d\n",sockconn[cli],liste_joueur[cli].sockid);
        write(sockconn[cli],msg,sizeof(msg));
        read(sockconn[cli],name,sizeof(name));
        strcpy(liste_joueur[cli].name,name);
        printf("%s, %s\n",name,liste_joueur[cli].name);
        sprintf(msg,"Bienvenue %s\n",name);
        write(sockconn[cli],msg,sizeof(msg));
    }
}