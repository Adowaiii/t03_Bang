#include "board.h"
#include "linkedlist.h"

#ifndef _PLAYER_H_
#define _PLAYER_H_

// 定義父類結構
typedef struct {
    int id;
    char BoardNum;
    sList CardinHand;
} Player;

// 建構函式宣告
void Player_Ctor(Player *this, int id, int BoardNum, sList CardinHand);

// 獲取父類屬性宣告
int Player_GetId(Player *this);
int Player_GetBoard(Player *this);
sList Player_GetCards(Player *this);
void Player_AddCards(Player *this);

#endif