#include "player.h"
#include "linkedlist.h"

// 父類建構函式實現
void Player_Ctor(Player *this, int id, int BoardNum, LinkedList CardinHand)
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

LinkedList Player_GetCards(Player *this){
    return this->CardinHand;
}

int _addCards(Player plyr, LinkedList list){
    
    addNode(plyr.CardinHand);

    return list.id;
}

void _delCards(LinkedList deck, int card_ID){
    
    delNode(deck);
    return 0;
}