#include "Player.h"

// 父類建構函式實現
void Player_Ctor(Player *this, int id, int BoardNum, LinkedList CardinHand)
{
    this->id = id;
    this->BoardNum = BoardNum;
    this->LinkedList = CardinHand;
}

int Animal_GetId(Player *this){
    return this->id;
}

char Player_GetBoard(Player *this){
    return this->BoardNum;
}

void Player_GetCards(Player *this){
    return this->CardinHand;
}