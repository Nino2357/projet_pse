#ifndef SERV_COINCHE_H
#define SERV_COINCHE_H

#include "structure.h"
#include "pse.h"

void partie(void);
void init_serveur(player *liste_joueur);
void preparation_partie(player *liste_joueur);
char* read_card(card c, char* carte);
deck creer_tas(void);

#endif