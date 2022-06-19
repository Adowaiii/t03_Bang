
#include "player.h"
void Player_Ctor(Player *this, int id, int BoardNum, card *CardinHand)
{
    this->id = id;
    this->BoardNum = BoardNum;
    this->CardinHand = CardinHand;
}

int Player_GetId(Player *this)
{
	return this->id;
}

int Player_GetBoard(Player *this)
{
	return this->BoardNum;
}

void Player_GetCards(Player *this)
{
	return print(this->CardinHand);
}
