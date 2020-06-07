#ifndef PREP_H
#define PREP_H

#include "structure.h"

deck creer_tas(void);
void shuffle(deck* deck);
void read_card(card c);
void read_hand(player p);
void read_deck(deck* tas);
void cut(deck* d, int i);
void concat_deck(deck* d1, deck* d2);
void distribuer(deck* tas, player ordre[4]);
int preparation(void);
bet annonce(player ordre[4]);

#endif