#include "structure.h"
#include "pse.h"




int main(int argc, char *argv[])
{
    struct sockaddr_in addr_serv;
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(3005);
    addr_serv.sin_addr.s_addr = INADDR_ANY;
    unsigned int lg_addr_cli;

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
    struct sockaddr_in addr_cli[4];
    int sockconn[4];
    char buff[20];
    int prem= true;
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
        read(sockconn[cli],buff,sizeof(buff));
        printf("%s\n",buff);
        printf("%d\n",sockconn[cli]);
        if (prem)
        {
            printf("Envoyez un msg: \n");
            scanf("%s",buff);
            write(sockconn[cli],buff,sizeof(buff));
            prem = false;
        }

    }
    return 0;


}
