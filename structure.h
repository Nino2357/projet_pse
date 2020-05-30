
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
    int team_id;
    deck hand;
}player;

typedef struct team
{
    int id;
    player p1;
    player p2;
    int score_hand;
    int score;
    deck team_deck;
}team;

typedef struct bet
{
    int color;
    int goal;
    team equipe;
}bet;
