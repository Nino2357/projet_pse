#include "structure.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/socket.h>
#include <stdbool.h>

/*
-Finir de corriger la synthaxe
-Rajouter :  couper  à la fin d'une main (pop et concatenation)
-Annonce (belote et re, 10 de der)
-Montrer la main au moment de la mise et a chaque tour
-Afficher les cartes jouées et sa main dans play_round
*/

deck creer_tas(void);
void shuffle(deck* deck);
void read_card(card c);
void read_hand(player p);
void read_deck(deck* tas);
void cut(deck* d, int i);
void concat_deck(deck* d1, deck* d2);

int main(void)
{
	srand (time (NULL));
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
    team0.p1= p1;
    team0.p2= p2;
    team1.p1= p1;
    team1.p2= p2;
    team0.id = 0;
    team1.id = 1;
    player ordre[4]={team0.p1,team1.p1,team0.p2,team1.p2};
    player ordre_distri[4]={team0.p1,team1.p1,team0.p2,team1.p2};
    team ordre_t[2]={team0,team1};
    deck jeu;
    team equipe[2] = {team0,team1};
    jeu = creer_tas();
    printf("test0\n");
    printf("test1\n");
    return 0;
}

deck creer_tas(void) //Crée le tas de 32 cartes dans l'ordre
{
    deck tas;
    tas.size=32;
    int compteur = 0;
    for(int couleur=0;couleur<4;couleur++) // Fais le tour des 4 couleurs
    {

    	for(int valeur=7;valeur<14;valeur++) //Ajoute les cartes du 7 au roi
        {
            card new;
            new.color=couleur;
            new.value = valeur;
            tas.tab[compteur]=new;
            compteur ++;
        }
        card new; //Ajoute l'As
        new.color=couleur;
        new.value = 1;
        tas.tab[compteur]=new;
        compteur ++;
   }
   return tas;

}

void shuffle(deck* deck){
    card temp;

    for(int i = 0; i<1000; i++){
        int hasard1 =rand()%(deck->size - 1);
        temp = deck->tab[hasard1];
        int hasard2 =rand()%(deck->size - 1);
        deck->tab[hasard1] = deck->tab[hasard2];
        deck->tab[hasard2] = temp;
    }

}

void read_card(card c)
{
    char* colors[4]={"coeur","carreau","pique","trefle"};
    char* values[13]={"As","2","3","4","5","6","7","8","9","10","Valet","Dame","Roi"};
    printf("%s de %s \n", values[c.value-1], colors[c.color]);
}

void read_hand(player p){
    for(int i=0; i<8; i++){
        read_card(p.hand.tab[i]);
    }
}

void read_deck(deck* tas){
    for(int i=0; i<tas->size; i++){
        read_card(tas->tab[i]);
    }
}
/*
void cut(deck* d, int i){
    printf("test2\n");
    deck *temp;
    printf("test3\n");
    int j=i;
    printf("j:%d/n",j);
    for(j=i; j<d->size; j++){
        printf("j:%d/n",j);
        //temp->tab[j-i] = d->tab[j];
        temp->size ++;
        }
    d->size=i;
    concat_deck(temp, d);
    d = temp;
}

void concat_deck(deck* d1, deck* d2){
    for(int i=0;i<d2->size;i++){
        d1->tab[d1->size]=d2->tab[i];
        d1->size ++;
    }
}
*/