#include "serveur_coinche.h"

int main(int argc, char *argv[])
{
    partie();
    return 0;
}

void partie(void)
{    
    player p0, p1, p2, p3; //Création des joueurs
    //Initalisation
    p0.id = 0;
    p1.id = 1;
    p2.id = 2;
    p3.id = 3;
    player liste_joueur[4]={p0,p1,p2,p3};
    init_serveur(liste_joueur);
    deck tas;
    tas = creer_tas();
    preparation_partie(liste_joueur,&tas);
    tour(liste_joueur,&tas);

}

void preparation_partie(player *liste_joueur, deck *jeu)
{
        
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
        write(liste_joueur[0].sockid,read_card(jeu->tab[c],carte),sizeof(carte));
        write(liste_joueur[1].sockid,read_card(jeu->tab[c],carte),sizeof(carte));
        write(liste_joueur[2].sockid,read_card(jeu->tab[c],carte),sizeof(carte));
        write(liste_joueur[3].sockid,read_card(jeu->tab[c],carte),sizeof(carte));
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
    shuffle(jeu);  //Mélange du tas
    distribuer(jeu,liste_player); //distribution du deck mélangé aux 4 joueurs
    affichage_main(liste_player);
    annonce(liste_player);
}
 
void affichage_main(player *liste_player)
{
    char carte[100];
    for(int j=0; j<8; j++)
    {   
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
    for(int i=0; i<(tas->size)/4; i++)
    {
        ordre[0].hand.tab[i].color=tas->tab[i*4].color;
        ordre[0].hand.tab[i].value=tas->tab[i*4].value;
        ordre[1].hand.tab[i].color=tas->tab[i*4+1].color;
        ordre[1].hand.tab[i].value=tas->tab[i*4+1].value;
        ordre[2].hand.tab[i].color=tas->tab[i*4+2].color;
        ordre[2].hand.tab[i].value=tas->tab[i*4+2].value;
        ordre[3].hand.tab[i].color=tas->tab[i*4+3].color;
        ordre[3].hand.tab[i].value=tas->tab[i*4+3].value;
    }
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
    return carte;
}

void annonce(player ordre[4])
{
    int abstention_max = 3;
    int abstention = 0;
    int fin = 0;
    bet *mise;
    mise = malloc(sizeof(bet));
    char tour[3];
    int *choix;
    choix = malloc(sizeof(int));
    int temp;
    mise->goal = 0; //Permet d'indiquer qu'aucune equipe n'a misé
    char msg[300];
    while (!fin)
    { 
        for(int t=0; t<4;t++)
        {
            sprintf(tour,"OK"); 
            write(ordre[t].sockid,tour,sizeof(tour));//J1
            for(int j=0; j<4;j++)
            {
                if (j!=t)
                {
                    sprintf(tour,"NO");
                    write(ordre[j].sockid,tour,sizeof(tour));
                }
            }
            read(ordre[t].sockid,choix,sizeof(choix));//R1
            if(*choix == 0) //Si le joueur ne souhaite pas miser
            {
                abstention ++;
                sprintf(msg,"\n%s (p%d) : Je passe\n",ordre[t].name,ordre[t].id);
                printf("%s",msg);
                write(ordre[0].sockid,msg,sizeof(msg)); //M1
                write(ordre[1].sockid,msg,sizeof(msg));
                write(ordre[2].sockid,msg,sizeof(msg));
                write(ordre[3].sockid,msg,sizeof(msg));
            }
            if (*choix !=0)
            {                    
                sprintf(msg,"\nCouleur : (0 = coeur, 1 = carreau, 2 = pique, 3 = trefle) ");
                write(ordre[t].sockid,msg,sizeof(msg));//W3
                read(ordre[t].sockid,&temp,sizeof(int*));//R2
                mise->color = temp;
                sprintf(msg,"Montant : (80 à 180 et 250 pour capot) ");
                write(ordre[t].sockid,msg,sizeof(msg));//w4
                read(ordre[t].sockid,&temp,sizeof(int*));//R3
                mise->goal=temp;
                mise->joueur = ordre[t];
                mise->equipe.id = ordre[t].team_id;
                abstention = 1; //Pour contrer le fait que au 1er tout il faille 4 abstention et seulement 3 aux autres
                sprintf(msg,"\n%s (p%d) :\nCouleur : %d \n(0 = coeur, 1 = carreau, 2 = pique, 3 = trefle)\nObjectif: %d \n", mise->joueur.name,mise->joueur.id,mise->color,mise->goal);
                printf("%s",msg);
                write(ordre[0].sockid,msg,sizeof(msg)); //M1
                write(ordre[1].sockid,msg,sizeof(msg));
                write(ordre[2].sockid,msg,sizeof(msg));
                write(ordre[3].sockid,msg,sizeof(msg));
            }
            if(abstention>abstention_max) //Detecte la fin des mises dans le while
            {
                fin = 1;
                write(ordre[0].sockid,&fin,sizeof(fin));//F1
                write(ordre[1].sockid,&fin,sizeof(fin));
                write(ordre[2].sockid,&fin,sizeof(fin));
                write(ordre[3].sockid,&fin,sizeof(fin));
                break;
            }
            if(abstention<=abstention_max)
            {
                fin = 0;
                write(ordre[0].sockid,&fin,sizeof(fin));//F1
                write(ordre[1].sockid,&fin,sizeof(fin));
                write(ordre[2].sockid,&fin,sizeof(fin));
                write(ordre[3].sockid,&fin,sizeof(fin));
            }
        }
    }
    if(mise->goal==0)
    {
        sprintf(msg,"\nPersonne n'a misé, on redistribue\n");
        printf("%s",msg);
        write(ordre[0].sockid,msg,sizeof(msg));//MF1
        write(ordre[1].sockid,msg,sizeof(msg));
        write(ordre[2].sockid,msg,sizeof(msg));
        write(ordre[3].sockid,msg,sizeof(msg));
    }
    else
    {
        sprintf(msg,"La mise finale est :\nCouleur : %d \n(0 = coeur, 1 = carreau, 2 = pique, 3 = trefle)\nObjectif: %d \nPar le joueur : %s (p%d)\n", mise->color,mise->goal,mise->joueur.name,mise->joueur.id);
        printf("%s",msg);
        write(ordre[0].sockid,msg,sizeof(msg));//MF1
        write(ordre[1].sockid,msg,sizeof(msg));
        write(ordre[2].sockid,msg,sizeof(msg));
        write(ordre[3].sockid,msg,sizeof(msg));
    } 
}
