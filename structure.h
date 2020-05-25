
//Structure

typedef struct card
{
    int color;
    int value;
};

typedef struct mise
{
    int color;
    int goal;
};

typedef struct deck
{
    int size;
    card tab[32];
};


typedef struct player
{
    int id;
    deck hand;
};

typedef struct team
{
    player p1;
    player p2;
    int score = 0;
    deck team_deck;
};
