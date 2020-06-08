#ifndef STRUCT_H
#define STRUCT_H

//Include
#include "pse.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/socket.h>
#include <stdbool.h>

//Structure


typedef struct card
{
    int color;
    int value;
}card;


typedef struct deck
{
    int size;
    card tab[32];
}deck;


typedef struct player
{
    int id; 
    int sockid; //Adresse de connection
    char name[10];
    int team_id;
    deck hand;
}player;

typedef struct team
{
    int id;
    player p0;
    player p1;
    int score_hand;
    int score;
    deck team_deck;
}team;

typedef struct bet
{
    int color;
    int goal;
    team equipe;
    player joueur;
}bet;

#endif