#include "card.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

typedef struct
{
    int id;
    int BoardNum;
    card CardinHand;
} Player;

void Player_Ctor(Player *this, int id, int BoardNum, card CardinHand);

int Player_GetId(Player *this);
int Player_GetBoard(Player *this);
card Player_GetCards(Player *this);

#endif
