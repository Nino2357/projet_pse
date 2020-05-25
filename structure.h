//Structure

typedef struct card
{
    int color;
    int value;
} *Card;

typedef struct mise
{
    int color;
    int goal;
} *Mise;

typedef struct deck
{
    int size;
    card tab[32];
} *Deck;


typedef struct player
{
    int id;
    deck hand;
} *Player;

typedef struct team
{
    player p1;
    player p2;
    int score;
    deck team_deck;
};
