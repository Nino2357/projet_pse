#include "structure.h"
#include "pse.h"




int main(int argc, char *argv[])
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
    char msg[20];
    printf("connexion reussie\nEnvoyer le msg :\n");
    scanf("%s",msg);
    write(sockfd,msg,sizeof(msg));
    read(sockfd,msg,sizeof(msg));
    printf("message du serveur : %s\n",msg);
    
    return 0;
}