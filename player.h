#ifndef _PLAYER_H_
#define _PLAYER_H_

// 定義父類結構
typedef struct {
    int id;
    char BoardNum;
    LinkedList CardinHand;
} Player;

// 建構函式宣告
void Player_Ctor(Player *this, int id, int BoardNum, LinkedList CardinHand);

// 獲取父類屬性宣告
int Player_GetId(Player *this);
char Player_GetBoard(Player *this);
void Player_GetCards(Player *this);

#endif