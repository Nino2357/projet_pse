#include "client_coinche.h"

int main(int argc, char *argv[])
{
    partie();
    return 0;
}
 
void partie(void)
{
    int sockfd;
    sockfd = init_serveur();
    preparation_partie(sockfd);
    tour(sockfd);
}
 
int init_serveur(void)
{
    struct sockaddr_in addr_serv;
    int sockfd= socket (AF_INET, SOCK_STREAM, 0);
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(3005);
    addr_serv.sin_addr.s_addr = INADDR_ANY;
    int retour = connect(sockfd, (struct sockaddr *) &addr_serv, sizeof(struct sockaddr_in));
    if(retour==-1)
    {
        perror ( "accept" );
        exit ( EXIT_FAILURE );

    }
    char msg[100];
    char name[10];
    printf("connexion reussie, attendez un peu svp\n");
    read(sockfd,msg,sizeof(msg));
    printf("%s\n",msg);
    scanf("%s",name);
    write(sockfd,name,sizeof(name));
    read(sockfd,msg,sizeof(msg));
    printf("message du serveur : %s\n",msg);
    return sockfd;
}  

void preparation_partie(int sockfd)
{ 
    //Affichage du paquet de cartes
    char msg[200];
    read(sockfd,msg,sizeof(msg));
    printf("%s\n",msg);
    char carte[100];
    for(int c=0; c<32;c++) 
    {
        read(sockfd,carte,sizeof(carte)); 
        printf("%s\n",carte);
    }

    //Affichage des équipes 
    char msg_equipe[200];
    read(sockfd,msg_equipe,sizeof(msg_equipe));
    printf("%s\n",msg_equipe);


}  

void tour(int sockfd)
{
    //Mélange
    //Distribution
    //Affichage de la main :
    printf("Votre main de départ est : \n");
    char carte[100];
    for(int j=0; j<8; j++)
    {
        read(sockfd,carte,sizeof(carte));
        printf("%s\n",carte);
    }
    annonce(sockfd);

}

void annonce(int sockfd)
{
    char msg[300];
    int *fin;
    int fin1 =0;
    fin = &fin1;
    int choix = 0;
    char tour[10];
    while (!*fin)
    { 
        printf("debut while\n");
        read(sockfd, tour, sizeof(tour));//J1
        printf("tour :%s\n", tour);
        if (!strcmp(tour,"OK"))
        {
            printf("tour ok\n");
            sprintf(msg,"Voulez vous miser ?");
            printf("%s",msg);
            sprintf(msg,"Oui (1) / Non (0) : ");
            printf("%s",msg);
            scanf("%d",&choix); 
            write(sockfd,&choix,sizeof(choix)); //R1 -Choix mise ou non
            if(choix==1)
            {
                printf("Dans choix\n");
                //Choix couleur
                read(sockfd,msg,sizeof(msg));//w3
                printf("%s",msg);
                scanf("%d",&choix);
                write(sockfd,&choix,sizeof(choix));//R2
                //Choix montant
                read(sockfd,msg,sizeof(msg));//W4
                printf("%s",msg);
                scanf("%d",&choix); 
                write(sockfd,&choix,sizeof(choix));//R3
            }
        }
        printf("fin tour \n");

        read(sockfd,msg,sizeof(msg)); //M1
        printf("%s",msg);
        read(sockfd, fin, sizeof(fin)); //F1

        printf("fin while, fin : %d \n",*fin);
    }
    read(sockfd,msg,sizeof(msg)); //MF1
    printf("%s",msg);
} 