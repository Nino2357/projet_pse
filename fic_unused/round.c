#include "round.h"











player play_round(player ordre[4], int atout, team ordre_t[2]){
    deck centre;
    centre.size=0;
    card best;
    int best_equipe;
    card choix1;
    player winner;
    printf("Premier joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", &choix1.value, &choix1.color);
    while(card_in_hand(choix1, ordre[0].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", &choix1.value, &choix1.color);
    }
    centre.tab[0] = choix1;
    centre.size ++;
    pop_card(ordre[0].hand,choix1);
    best = choix1;
    best_equipe=1;
    winner = ordre[0];
    int couleur = choix1.color;

    card choix2;
    printf("Deuxième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", &choix2.value, &choix2.color);
    while(card_in_hand(choix1, ordre[1].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", &choix2.value, &choix2.color);
    }
    centre.tab[1] = choix2;
    centre.size ++;
    pop_card(ordre[1].hand,choix1); // ZPEFOZPOEPFOSPFODPFB pas encore fait
    if (compare(best,choix2,atout,couleur)==2){
        best = choix2;
        best_equipe=2;
        winner = ordre[1];
    }    
    

    card choix3;
    printf("Troisième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", &choix3.value, &choix3.color);
    while(card_in_hand(choix3, ordre[2].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", &choix3.value, &choix3.color);
    }
    centre.tab[2] = choix3;
    centre.size ++;
    pop_card(ordre[2].hand,choix1);
    if (compare(best,choix3,atout,couleur)==2){
        best = choix3;
        best_equipe=1;
        winner = ordre[2];
    }   

    card choix4;
    printf("Quatrième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", &choix4.value, &choix4.color);
    while(card_in_hand(choix4, ordre[3].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", &choix4.value, &choix4.color);
    }
    centre.tab[3] = choix4;
    centre.size ++;
    pop_card(ordre[3].hand,choix1);
    if (compare(best,choix4,atout,couleur)==2){
        best = choix4; 
        best_equipe=2; 
        winner = ordre[3];
    }
    concat_deck(ordre_t[best_equipe-1].team_deck, centre);
    return winner;
}