#include "annonce.h"


int main(void)
{
    int list_player[4]={0,1,2,3};
    player p1;
    player p2;
    player p3;
    player p0;
    team team0;
    team team1;
    team0.score=0;
    team1.score=0;
    p0.id = 0;
    p1.id = 1;
    p2.id = 2;
    p3.id = 3;
    team0.p1= p0;
    team0.p2= p2;
    team1.p1= p1;
    team1.p2= p3;
    p0.equipe = team0:
    
    team0.id = 0;
    team1.id = 1;
    player ordre[4]={team0.p1,team1.p1,team0.p2,team1.p2};
    player ordre_distri[4]={team0.p1,team1.p1,team0.p2,team1.p2};
    annonce(ordre_distri);
    return 0;
}

bet annonce(player ordre[4])
{
    int abstention_max = 3;
    int abstention = 0;
    bool fin = false;
    bet mise;
    int choix = 0;
    mise.goal = 0; //Permet d'indiquer qu'aucune equipe n'a misé
    while (!fin)
    {
        for(int t=0; t<4;t++)
        {
            printf("Joueur %d voulez vous miser ? :\n",ordre[t].id);
            printf("Oui (1) / Non (0) : ");
            scanf("%d",&choix);
            if(choix == 0) //Si le joueur ne souhaite pas miser
            {
                abstention ++;
            }
            else
            {
                printf("\nCouleur : (-1 si rien) ");
                scanf("%d",&mise.color);
                printf("\nMontant :");
                scanf("%d",&mise.goal);
                mise.joueur = ordre[t];
                mise.equipe = ordre[t].team_id;
            }   
            t++; //On change joueur
            if(abstention>abstention_max) //Detecte la fin des mises dans le for
            {
                printf("Fin de la phase d'annonce\n");
                fin = true;
                break;
            }
        }
        if(abstention>abstention_max) //Detecte la fin des mises dans le while
            {
                fin = true;
                break;
            }
    }
    if(mise.goal==0)
    {
        printf("Personne n'a misé, on redistribue\n");
    }
    else
    {
        printf("LA mise est : %d %d par le joueur : %d de l'équipe : %d\n", mise.color,mise.goal,mise.joueur,mise.equipe);
    }
}

