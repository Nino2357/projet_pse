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
    deck tas;
    preparation_partie(liste_joueur);
    printf("-1");
    tour(liste_joueur,&tas);
    printf("ap tour");
}

void preparation_partie(player *liste_joueur)
{
        
    //Création du paquet de cartes
    deck jeu;
    jeu = creer_tas(); //Création d'un tas ordonné
    //Affichage du paquet de cartes
    char msg[200];
    sprintf(msg,"Affichage du paquet de cartes: \n");
    write(liste_joueur[0].sockid,msg,sizeof(msg));
    write(liste_joueur[1].sockid,msg,sizeof(msg));
    write(liste_joueur[2].sockid,msg,sizeof(msg));
    write(liste_joueur[3].sockid,msg,sizeof(msg));
    char carte[100];
    for(int c=0; c<32;c++)
    {
        write(liste_joueur[0].sockid,read_card(jeu.tab[c],carte),sizeof(carte));
        write(liste_joueur[1].sockid,read_card(jeu.tab[c],carte),sizeof(carte));
        write(liste_joueur[2].sockid,read_card(jeu.tab[c],carte),sizeof(carte));
        write(liste_joueur[3].sockid,read_card(jeu.tab[c],carte),sizeof(carte));
    }

    //Affichage des equipes
    char msg_equipe[200];
    sprintf(msg_equipe,"\n\nVoici les equipes :\nequipe 1 : %s %s\nequipe 2 : %s %s\n",liste_joueur[0].name,liste_joueur[2].name,liste_joueur[1].name,liste_joueur[3].name);
    write(liste_joueur[0].sockid,msg_equipe,sizeof(msg_equipe));
    write(liste_joueur[1].sockid,msg_equipe,sizeof(msg_equipe));   
    write(liste_joueur[2].sockid,msg_equipe,sizeof(msg_equipe));
    write(liste_joueur[3].sockid,msg_equipe,sizeof(msg_equipe));
    
}

void tour(player *liste_player, deck *jeu)
{
    printf("0");
    shuffle(jeu);  //Mélange du tas
    printf("1");
    distribuer(jeu,liste_player); //distribution du deck mélangé aux 4 joueurs
    printf("2");
    affichage_main(liste_player);
}
 
void affichage_main(player *liste_player)
{
    char carte[100];
    printf("Joueur %d : \n", 0);
    for(int j=0; j<8; j++)
    {   
        printf("j: %d, carte %s\n",j,read_card(liste_player[0].hand.tab[j],carte));
        write(liste_player[0].sockid,read_card(liste_player[0].hand.tab[j],carte),sizeof(carte));
        write(liste_player[1].sockid,read_card(liste_player[1].hand.tab[j],carte),sizeof(carte));
        write(liste_player[2].sockid,read_card(liste_player[2].hand.tab[j],carte),sizeof(carte));
        write(liste_player[3].sockid,read_card(liste_player[3].hand.tab[j],carte),sizeof(carte));

    
    }
    
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
        sprintf(msg,"Bienvenue joueur p%d \nVeillez entrez votre nom svp :\n",cli);
        liste_joueur[cli].sockid = sockconn[cli];
        write(liste_joueur[cli].sockid,msg,sizeof(msg));
        read(sockconn[cli],name,sizeof(name));
        strcpy(liste_joueur[cli].name,name);
        printf("Connexion du joueur p%d de nom: %s (sockid: %d)\n",cli,liste_joueur[cli].name,liste_joueur[cli].sockid);
        sprintf(msg,"Bienvenue %s\n",name);
        write(liste_joueur[cli].sockid,msg,sizeof(msg));
    }
}


deck creer_tas(void) //Crée le tas de 32 cartes dans l'ordre
{
    deck tas;
    tas.size=32;
    int compteur = 0;
    for(int couleur=0;couleur<4;couleur++) // Fais le tour des 4 couleurs
    {

    	for(int valeur=7;valeur<14;valeur++) //Ajoute les cartes du 7 au roi
        {
            card new;
            new.color=couleur;
            new.value = valeur;
            tas.tab[compteur]=new;
            compteur ++;
        }
        card new; //Ajoute l'As
        new.color=couleur;
        new.value = 1;
        tas.tab[compteur]=new;
        compteur ++;
   }
   return tas;

}

void shuffle(deck* deck)
{
    card temp;

    for(int i = 0; i<1000; i++){
        int hasard1 =rand()%(deck->size - 1);
        temp = deck->tab[hasard1];
        int hasard2 =rand()%(deck->size - 1);
        deck->tab[hasard1] = deck->tab[hasard2];
        deck->tab[hasard2] = temp;
    }

}

void distribuer(deck* tas, player ordre[4]){
    for(int i=0; i<(tas->size)/4; i++){
        //printf("%d %d \n",tas->size,i);
        ordre[0].hand.tab[i]=tas->tab[i*4];
        tas->tab[i].value=0;
        ordre[1].hand.tab[i]=tas->tab[i*4+1];
        tas->tab[i*4+1].value=0;
        ordre[2].hand.tab[i]=tas->tab[i*4+2];
        tas->tab[i*4+2].value=0;
        ordre[3].hand.tab[i]=tas->tab[i*4+3];
        tas->tab[i*4+3].value=0;
        //printf("%d %d \n",ordre[0].hand.tab[i].color,ordre[0].hand.tab[i].value);
    }
    //read_hand(ordre[0]);
    ordre[0].hand.size=8;
    ordre[1].hand.size=8;
    ordre[2].hand.size=8;
    ordre[3].hand.size=8;
}



char* read_card(card c,char *carte)
{
    char* colors[4]={"coeur","carreau","pique","trefle"};
    char* values[13]={"As","2","3","4","5","6","7","8","9","10","Valet","Dame","Roi"};
    sprintf(carte,"%s de %s", values[c.value-1], colors[c.color]);
    //printf("%s de %s", values[c.value-1], colors[c.color]);
    return carte;
}