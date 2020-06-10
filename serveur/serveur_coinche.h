#ifndef SERV_COINCHE_H
#define SERV_COINCHE_H

#include "structure.h"
#include "pse.h"

void partie(void);
void init_serveur(player *liste_joueur);
void preparation_partie(player *liste_joueur, deck *jeu);
char* read_card(card c, char* carte);
deck creer_tas(void);
void tour(player *liste_player, deck *jeu);
void shuffle(deck* deck);
void distribuer(deck* tas, player ordre[4]);
void affichage_main(player *liste_player);

#endif