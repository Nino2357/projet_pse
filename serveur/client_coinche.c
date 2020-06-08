#include "client_coinche.h"

int main(int argc, char *argv[])
{
    partie();
    return 0;
}

void partie(void)
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
    printf("connexion reussie\n");
    read(sockfd,msg,sizeof(msg));
    printf("%s\n",msg);
    scanf("%s",name);
    write(sockfd,name,sizeof(name));
    read(sockfd,msg,sizeof(msg));
    printf("message du serveur : %s\n",msg);
}