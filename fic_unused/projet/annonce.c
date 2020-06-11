#include "annonce.h"


int main(void)
{
    //int list_player[4]={0,1,2,3};
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
    p0.team_id = 0;
    p1.team_id = 1;
    p2.team_id = 0;
    p3.team_id = 1;    
    team0.id = 0;
    team1.id = 1;
    //player ordre[4]={team0.p1,team1.p1,team0.p2,team1.p2};
    //team ordre_t[2]={team0,team1};
    player ordre_distri[4]={p0,p2,p1,p3};
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
            printf("\n\nJoueur %d voulez vous miser ? :\n",ordre[t].id);
            printf("Oui (1) / Non (0) : ");
            scanf("%d",&choix);
            if(choix == 0) //Si le joueur ne souhaite pas miser
            {
                abstention ++;
            }
            else
            {
                printf("\nCouleur : (0 = coeur, 1 = carreau, 2 = pique, 3 = trefle) ");
                scanf("%d",&mise.color);
                printf("\nMontant : (80 à 180 et 250 pour capot) ");
                scanf("%d",&mise.goal);
                mise.joueur = ordre[t];
                mise.equipe.id = ordre[t].team_id;
                abstention = 1; //Pour contrer le fait que au 1er tout il faille 4 abstention et seulement 3 aux autres
            }   
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
        printf("La mise est : %d %d par le joueur : %d de l'équipe : %d\n", mise.color,mise.goal,mise.joueur.id,mise.equipe.id);
    }
    return mise;
}

