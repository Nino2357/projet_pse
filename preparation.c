#include "define.h"
#include "structure.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/socket.h>

deck creer_tas(void); //creer le deck de départ avec 32 cartes
deck shuffle(deck deck); //melange un deck existant (utile uniquement lors de la premiere donne)
void distribuer(deck tas, player ordre[4]); //Distribue les cartes dans les mains des joueurs en respectant l'ordre de la donne
void read_card(card c); // print le contenu d'une carte
void read_hand(player p); //print le contenu des cartes de la main d'un joueur (encore à implémanter dans la fonction annonce avant de demander au joueurs ce qu'il compte miser)
bet annonce(player ordre[4], team ordre_t[2]); // Correspond a la phase d'annonce de la coinche. Les joueurs doivent faire une premiere annonce, si aucune n'a ete effectué on redistribue. Si une annonce a ete effectue on refait un tour pour voir s'il y a surenchere
int card_in_hand(card choix, deck hand); //verifie si une carte est dans une main donnee. Retour 1 si oui, 0 sinon
int ind(int v, int tab[8]; int size); // Donne l'indice d'un nombre dans un tableau d'int (je ne savais pas si la fonction ete deja implementee)
int compare_value_a(int v1, int v2); //Permet de comparer deux valeurs de carte lorsqu'elles sont de la couleur de l'atout. Retourne 1 si la premiere et plus forte et 2 sinon
int compare_value_na(int v1, int v2); //Permet de comparer deux valeurs de carte lorsqu'elles ne sont pas de la couleur de l'atout. Retourne 1 si la premiere et plus forte et 2 sinon
int compare(card carte1, card carte2, int atout, int couleur ); //compare deux cartes. Retourne 1 si la premiere et plus forte et 2 sinon
void concat_deck(deck d1, deck d2); // pour ajouter un deck a la suite d'un autre. Utile en fin de tour pour garder une trace du deck.
void play_round(player ordre[4], int atout, team ordre_t[2]); // effectue un tour de table. on entre l'ordre des joueurs et l'ordre des equipes ainsi que l'atout (pour comparer les cartes)
void scoref(team ordre_t, int atout); // calcul et print les scores des deux equipes. Maj le score dans les equipes aussi.
void play_hand(player ordre[4], int atout, team ordre_t[2], bet mise, team equipes[2]); // effectue une main complete (8 tours)


int main(void)
{
    /* On récupère les ID des 4 joueurs
     et on les stock dans une liste d'int*/
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
    team0.p={p0;p2};
    team1.p={p1;p3};
    team0.id = 0;
    team1.id = 1;
    player ordre[4]={team1.p[0],team2.p[0],team1.p[1],team2.p[1]};
    player ordre_distri[4]={team1.p[0],team2.p[0],team1.p[1],team2.p[1]};
    team ordre_t[2]={team1,team2}
    deck jeu;
    jeu = creer_tas();
    shuffle(jeu)
    while(team1.score<1000 && team2.score<1000){
        distribuer(jeu,ordre);
        //ici on print les mains aux joueurs.
        bet mise =  annonce(ordre,ordre_t);
        while(mise.goal==0){
            printf("On redistribue");
            distribuer(jeu,ordre);
            bet mise = annonce(ordre,ordre_t);
        }
        play_hand(ordre,mise.color,ordre_t)
        
    }
    return 0;
}

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

deck shuffle(deck deck){
    deck new_deck;
    new_deck.size= 0;
    int compteur = 0;
    while (deck.size >= new_deck.size){
        int hasard = (rand()/INT_MAX)*(deck.size);
        if(deck.tab[hasard] != NULL){
            new_deck.tab[compteur] = deck.tab[hasard];
            deck.tab[hasard] = NULL;
            new_deck.size ++;
        }
    }
    return new_deck;
}

void distribuer(deck tas, player ordre[4]){
    for(int i=0; (i<tas.size)/4; i++){
        ordre[0].hand.tab[i]=tas.tab[i];
        tas.tab[i]=NULL
        ordre[1].hand.tab[i]=tas.tab[i+1];
        tas.tab[i+1]=NULL
        ordre[2].hand.tab[i]=tas.tab[i+2];
        tas.tab[i+2]=NULL
        ordre[3].hand.tab[i]=tas.tab[i+3];
        tas.tab[i+3]=NULL
    }
    ordre[0].hand.size=8;
    ordre[1].hand.size=8;
    ordre[2].hand.size=8;
    ordre[3].hand.size=8;
}

void read_card(card c){
    char colors[4]={"coeur","carreau","pique","trefle"};
    char values[13]={"As","2","3","4","5","6","7","8","9","10","Valet","Dame","Roi"}
    printf("%s de %s \n", values[c.value], colors[c.color]);
}


void read_hand(player p){
    for(int i=0; i<8; i++){
        read_card(p.hand.tab[i]);
    }
}


bet annonce(player ordre[4], team ordre_t[2]){
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
                        mise.goal=0;
                        return mise;
                    }
                    else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise.goal);
                        last_betting=3;
                    }  
                }
                else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise.goal);
                        last_betting=2;
                }
            }
            else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise.goal);
                        last_betting=1;
            }
        }
        else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise.goal);
                        last_betting=0;
        }
    }
    //surenchere
    while(compt<3){
        printf("Voulez vous surenchérir? y/n")
        char will;
        scanf("%s",will);
        if(will!="y"){
            printf("Voulez vous surenchérir?  y/n  \n");
            scanf("%s",will);
            if(will!="y"){
                printf("Troisième joueur, voulez vous miser?  y/n  \n");
                scanf("%s",will);
                if(will!="y"){
                    return mise;
                    }
                else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins %d, 160 = capot et 200 = coinche)",mise.goal);
                        scanf("%d",mise.goal);
                        last_betting=2;
                }
            }
            else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise.goal);
                        last_betting=1;
            }
        }
        else{
                        printf("Quelle couleur misez vous? (1 = coeur, 2 = carreau, 3 = pique, 4 = trefle)");
                        scanf("%d",mise.color);
                        printf("Combien misez vous? (Au moins 80, 160 = capot)");
                        scanf("%d",mise.goal);
                        last_betting=0;
        }
    }
    }
    mise.equipe = ordre_t[last_betting];
}




int card_in_hand(card choix, deck hand){
    for(int i=0; i<hand.size; i++)
        if(choix==hand.tab[i])
            return 1;
    return 0;
}

int ind(int v, int tab[8]; int size){
    for(int i=0; i<size; i++){
        if(tab[i]==v)
            return i;
    }
    return -1;
}

int ind_c(card c, deck d){
    for(int i=0; i<size; i++){
        if(d.tab[i]==v)
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




int compare(card carte1, card carte2, int atout, int couleur ){
    if(carte2.color != couleur && carte2.color != atout)
        return 1;
    if(carte1.color!=atout && carte2.color == atout)
        return 2
    if(carte1.color==atout && carte2.color != atout)
        return 1;
    if(carte1.color==atout && carte2.color == atout){
        if(compare_value_a(carte1.value,carte2.value)==1){
            return 1;
        }
        return 2;
    }
    if(carte1.color==couleur && carte2.color == couleur){
        if(compare_value_na(carte1.value,carte2.value)==1){
            return 1;
        }
        return 2;
    }
}


void concat_deck(deck d1, deck d2){
    for(i=0;i<d2.size;i++){
        d1[d1.size]=d2[i];
        d1.size ++;
    }
}

void pop_card(deck d, card c){
    int ind = ind_c(c,d);
    if(ind!=-1){
        for(int i; i < (d.size-ind)){
            d.tab[i+ind] = d.tab[i+ind+1]; 
        }
        d.size = d.size -1;
    }
}

player play_round(player ordre[4], int atout, team ordre_t[2]){
    deck centre;
    centre.size=0;
    card best;
    int best_equipe;
    card choix1;
    player winner;
    printf("Premier joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix1.value, choix1.color);
    while(card_in_hand(choix, ordre[0].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix1.value, choix1.color);
    }
    centre.tab[0] = choix1;
    centre.size ++;
    pop_card(ordre[0].hand,choix1)
    best = choix1;
    best_equipe=1;
    winner = ordre[0]
    int couleur = choix1.color;

    card choix2;
    printf("Deuxième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix2.value, choix2.color);
    while(card_in_hand(choix, ordre[1].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix2.value, choix2.color);
    }
    centre.tab[1] = choix2;
    centre.size ++;
    pop_card(ordre[1].hand,choix1); // ZPEFOZPOEPFOSPFODPFB pas encore fait
    if (compare(best,choix2,atout,couleur)==2){
        best = choix2;
        best_equipe=2;
        winner = ordre[1]
    }    
    

    card choix3;
    printf("Troisième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix3.value, choix3.color);
    while(card_in_hand(choix, ordre[2].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix3.value, choix3.color);
    }
    centre.tab[2] = choix3;
    centre.size ++;
    pop_card(ordre[2].hand,choix1)
    if (compare(best,choix3,atout,couleur)==2){
        best = choix3;
        best_equipe=1;
        winner = ordre[2]
    }   

    card choix4;
    printf("Quatrième joueur, quelle carte souhaitez vous jouer? (valeur couleur");
    scanf("%d %d", choix4.value, choix4.color);
    while(card_in_hand(choix, ordre[3].hand)==0){
        printf("mauvaise entrée recommencez");
        scanf("%d %d", choix4.value, choix4.color);
    }
    centre.tab[3] = choix4;
    centre.size ++;
    pop_card(ordre[3].hand,choix1)
    if (compare(best,choix4,atout,couleur)==2){
        best = choix4; 
        best_equipe=2; 
        winner = ordre[3]
    }
    concat_deck(ordre_t[best_equipe-1].deck, centre);
    return winner
}

void change_order(player ordre[4], team ordre_t[2], player winner, team equipes[2]){ 
    if(ordre[0].id != winner.id){ //on verifie que ce ne soit pas le premier joueur qui soit deja gagnant et donc que l'ordre change bien
        for(int i; i<4; i++){
            ((winner.id) + i) % 4
            ordre[i] = (equipes[(((winner.id) + i) % 4)/2].p)[(((winner.id) + i) % 4)%2] // calcul complexe mdr. On change l'ordre et on veut recuperer les bon player. on se sert donc de l'ordre des equipes pour recuper les joueurs dans les equipes et avec un sage usage des quotients et reste changer l'ordre.
        }
        if(ordre[0].id%2==0){
            if(ordre_t[0].id!=0){
                team temp= ordre_t[0];
                ordre_t[0]=ordre_t[1];
                ordre_t[1]=temp;
            }
        }
    }
}


void scoref(team ordre_t, int atout){
    int val_atout[13] = {11,0,0,0,0,0,0,0,14,10,20,3,4};
    int val_natout[13] = {11,0,0,0,0,0,0,0,0,10,2,3,4};
    for(int i; i<2; i++){
        for(int j; j<ordre_t[i].team_deck; j++){
            if(i<ordre_t[i].team_deck[j].color == atout)
                ordre_t[i].score_hand = ordre_t[i].score_hand + val_atout[i<ordre_t[i].team_deck[j].value-1];
            else
                ordre_t[i].score_hand = ordre_t[i].score_hand + val_natout[i<ordre_t[i].team_deck[j].value-1];
        }
        printf("Le score de l'equipe %d est %d", ordre_t.id, ordre_t[i].score_hand);
    }
}

void play_hand(player ordre[4], team ordre_t[2], bet mise, team equipes[2]){
    for(int i=0; i<8; i++){
        // A chaque tour d'une main, il faut: changer l'ordre en fonction du gagnant du tour precedent,  calculer et afficher les scores)
        change_order(ordre, ordre_t, ordre[play_round(ordre, mise.color, ordre_t, equipes)]);
        scoref(ordre_t, mise.color);
    }
    //calcul final des scores et ajout dans le score
    // On commence par l'équipe qui a mise
    if(ordre_t[0].id==mise.team.id){
        if(ordre_t[0].score_hand<mise.goal){ //Premier cas, les preneurs chutent
            ordre_t[1].score = ordre_t[1].score + mise.goal + 160; //Les defenseurs marquent la mise annoncee et 160 points de chute
        }
        else{
            ordre_t[0].score = ordre_t[0].score + mise.goal + ordre_t[0].score_hand; //s'ils ne chutent pas alors ils marquent le contrat et les points effectuees
            ordre_t[1].score = ordre_t[1].score + ordre_t[1].score_hand; //les defenseurs marquent leurs points de la main
        }
    }
    else{
        if(ordre_t[1].score_hand<mise.goal){ //Premier cas, les preneurs chutent
            ordre_t[0].score = ordre_t[0].score + mise.goal + 160; //Les defenseurs marquent la mise annoncee et 160 points de chute
        }
        else{
            ordre_t[1].score = ordre_t[1].score + mise.goal + ordre_t[1].score_hand; //s'ils ne chutent pas alors ils marquent le contrat et les points effectuees
            ordre_t[0].score = ordre_t[0].score + ordre_t[0].score_hand; //les defenseurs marquent leurs points de la main
        }
    }
}