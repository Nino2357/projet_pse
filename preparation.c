#include "define.h"
#include "structure.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/socket.h>

deck creer_tas(void)
{
    deck tas;
    tas.size=32;
    int compteur = 0;
    for(int valeur=7;valeur<15;valeur++)
    {
        for(int couleur=0;couleur<4;couleur++)
        {
            card new;
            new.color=couleur;
            new.value = valeur;
            tas.tab[compteur]=new;
        }
    }
}

int main(void)
{

    return 0;
}

void init(void)
{
    /* On récupère les ID des 4 joueurs
     et on les stock dans une liste d'int*/
    int list_player[4]={0,1,2,3};
    team team1;
    team team2;
    team1.p1 = 0;
    team1.p2 = 1;
    team2.p1 = 2;
    team2.p2 = 3;
    for(int i=0;i<32;i++)
    {
        int hasard = (rand()/INT_MAX)*(32-i);

    }

}

