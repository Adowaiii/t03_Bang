#include "player.h"
#include "linkedlist.h"

// 父類建構函式實現
void Player_Ctor(Player *this, int id, int BoardNum, sList CardinHand)
{
    this->id = id;
    this->BoardNum = BoardNum;
    this->CardinHand = CardinHand;
}

int Player_GetId(Player *this){
    return this->id;
}

int Player_GetBoard(Player *this){
    return this->BoardNum;
}

sList Player_GetCards(Player *this){
    return this->CardinHand;
}

int _addCards(Player plyr, sList list){
    
    addNode(&plyr.CardinHand, list.pTail);
    return list.pParam;
}

void _delCards(sList deck, int card_ID){
    
    delNode(&deck, card_ID);
    return 0;
}