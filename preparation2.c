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
            compteur ++;
        }
    }
}

int main(void)
{
    /* On récupère les ID des 4 joueurs
     et on les stock dans une liste d'int*/
    int list_player[4]={0,1,2,3};
    team team1;
    team team2;
    team1.score=0;
    team2.score=0;
    team1.p1 = 0;
    team1.p2 = 1;
    team2.p1 = 2;
    team2.p2 = 3;
    player ordre[4]={team1.p1,team2.p1,team1.p2,team2.p2};
    team ordre_t[2]={team1,team2}
    deck jeu;
    jeu = creer_tas();
    shuffle(jeu)
    while(team1.score<1000 && team2.score<1000){
        distribuer(jeu,ordre);
        //ici on print les mains aux joueurs.
        bet mise =  annonce(ordre,ordre_t);
        while(mise->goal==0){
            printf("On redistribue");
            distribuer(jeu,ordre);
            bet mise =  annonce(ordre,ordre_t);
        }
        tour(ordre, atout, ordre_t)
    }
    return 0;
}
deck shuffle(deck deck){
    deck new_deck;
    new_deck.size= 0;
    int compteur = 0;
    while (deck.size >= new_deck.size){
        int hasard = (rand()/INT_MAX)*(deck.size);
        if(deck -> tab[hasard] != NULL){
            new_deck -> tab[compteur] = deck -> tab[hasard];
            deck -> tab[hasard] = NULL;
            new_deck.size ++;
        }
    }
    return new_deck;
}

void distribuer(deck tas, player* ordre){
    for(int i=0; (i<tas -> size)/4; i++){
        ordre[0]->hand->tab[i]=tas->tab[i];
        tas->tab[i]=NULL
        ordre[1]->hand->tab[i]=tas->tab[i+1];
        tas->tab[i+1]=NULL
        ordre[2]->hand->tab[i]=tas->tab[i+2];
        tas->tab[i+2]=NULL
        ordre[3]->hand->tab[i]=tas->tab[i+3];
        tas->tab[i+3]=NULL
    }
    ordre[0]->hand->size=8;
    ordre[1]->hand->size=8;
    ordre[2]->hand->size=8;
    ordre[3]->hand->size=8;
}


bet annonce(player* ordre, team* ordre_t){
    bet mise;
    int compt = 0;
    int last_betting;
    // premiere mise
    while(a_mise==0){
        char will;
        printf("Premier joueur, voulez vous miser?  y/n  \n");
        scanf("%s",will);
        if(will!="y"){
            printf("Second joueur, voulez vous miser?  y/n  \n");
            scanf("%s",will);
            if(will!="y"){
                printf("Troisième joueur, voulez vous miser?  y/n  \n");
                scanf("%s",will);
                if(will!="y"){
                    printf("Dernier joueur, voulez vous miser?  y/n  \n");
                    scanf("%s",will);
                    if(will!="y"){
                        mise->goal=0;
                        return mise
                    }
                    else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise->color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise->goal);
                        last_betting=3;
                    }  
                }
                else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise->color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise->goal);
                        last_betting=2;
                }
            }
            else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise->color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise->goal);
                        last_betting=1;
            }
        }
        else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise->color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise->goal);
                        last_betting=0;
        }
    }
    //Deuxieme mise
    while(compt<3){
        
    }
}




int card_in_hand(card choix, deck hand){
    for(int i=0; i<hand -> size; i++)
        if(choix==hand->tab[i])
            return 1
    return 0
}

int ind(int v, int* tab; int size){
    for(int i=0; i<size; i++){
        if(tab[i]==v)
            return i;
    }
    return -1;
}

int compare_value_a(int v1, int v2){
    int tab_valeur[8]={7;8;12;13;10;1;9;11};
    if(ind(v1,tab_valeur,8)>ind(v2,tab_valeur_a,8))
        return 1;
    return 2;
}
int compare_value_na(int v1, int v2){
    int tab_valeur[8]={7;8;9;11;12;13;10;1};
    if(ind(v1,tab_valeur)>ind(v2,tab_valeur_a))
        return 1;
    return 2;
}




int compare(card carte1, card carte2, int atout, int couleur )
    if(carte2->color != couleur && carte2->color != atout)
        return 1;
    if(carte1->color!=atout && carte2 -> color == atout)
        return 2
    if(carte1->color==atout && carte2 -> color != atout)
        return 1;
    if(carte1->color==atout && carte2 -> color == atout){
        if(compare_value_a(carte1->value,carte2->value)==1){
            return 1;
        }
        return 2;
    }
    if(carte1->color==couleur && carte2 -> color == couleur){
        if(compare_value_na(carte1->value,carte2->value)==1){
            return 1;
        }
        return 2;
    }



void concat_deck(deck d1, deck d2){
    for(i=0;i<d2->size;i++){
        d1[d1->size]=d2[i];
        d1->size ++;
    }
}

void tour(player* ordre, int atout, team* ordre_t){
    deck centre;
    centre->size=0;
    card best;
    int best_equipe;
    card choix1;
    printf("Premier joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("d* %d", choix1 -> value, choix1 -> color);
    while(card_in_hand(choix, ordre[0]->hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix1 -> value, choix1 -> color);
    }
    centre->tab[0] = choix1;
    centre->size ++;
    pop_card(ordre[0]->hand,choix1)
    best = choix1;
    best_equipe=1;
    int couleur = choix1 -> color;

    card choix2;
    printf("Deuxième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix2 -> value, choix2 -> color);
    while(card_in_hand(choix, ordre[1]->hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix2 -> value, choix2 -> color);
    }
    centre->tab[1] = choix2;
    centre->size ++;
    pop_card(ordre[1]->hand,choix1)
    if (compare(best,choix2,atout,couleur)==2){
        best = choix2;
        best_equipe=2;
    }    
    

    card choix3;
    printf("Troisième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix3 -> value, choix3 -> color);
    while(card_in_hand(choix, ordre[2]->hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix3 -> value, choix3 -> color);
    }
    centre->tab[2] = choix3;
    centre->size ++;
    pop_card(ordre[2]->hand,choix1)
    if (compare(best,choix3,atout,couleur)==2){
        best = choix3;
        best_equipe=1;
    }   

    card choix4;
    printf("Quatrième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix4 -> value, choix4 -> color);
    while(card_in_hand(choix, ordre[3]->hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix4 -> value, choix4 -> color);
    }
    centre->tab[3] = choix4;
    centre->size ++;
    pop_card(ordre[3]->hand,choix1)
    if (compare(best,choix4,atout,couleur)==2){
        best = choix4; 
        best_equipe=2; 
    }
    concat_deck(ordre_t[best_equipe-1]->deck, centre);
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
    deck jeu;
    jeu = creer_tas();
    shuffle(jeu)
    for(int i=0;i<32;i++)
    {
        int hasard = (rand()/INT_MAX)*(32-i);

    }

}

