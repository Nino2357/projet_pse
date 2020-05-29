
//Structure

typedef struct card
{
    int color;
    int value;
}card;

typedef struct mise
{
    int color;
    int goal;
}mise;

typedef struct deck
{
    int size;
    card tab[32];
}deck;


typedef struct player
{
    int id;
    deck hand;
}player;

typedef struct team
{
    player p1;
    player p2;
    int score;
    deck team_deck;
}team;
