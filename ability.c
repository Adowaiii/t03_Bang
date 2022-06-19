#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "board.h"
#include "player.h"
#include "card.h"
#include "character.h"
#include "ability.h"

#include <stdbool.h>

int check (int i, int list[3]){
    if (i > 3 || i < 0)
        return 0;  
    if (list[i] == 1)
        return 1;
    return 0;      
}

//Lucky Duke
//能力：當發生判定需要抽牌時，他可以抽兩張，並選擇一張當要判定的牌，
//判定結束後抽起來的兩張都要丟棄。Ex:【酒桶】判定時，他可以抽兩張，
//選擇一張當作要拿來判定的牌。

card _LuckyDuke_(Player player, card *deck, card *deadwood) {
    
    int chose;
    card *drawn;
    for (int i=0;i<2;i++)
        draw(player.CardinHand, drawn, 1);
    printf("Which do you want to choose?\n\n");
    for (int i=0;i<2;i++){
		drawn = drawn->next;
		printf("\"%d\" %s ", i, drawn->name);
	} 
    printf("\n");
    scanf("%d", &chose);
    card *chosen;
    for (int i=0;i<2;i++){
		drawn = drawn->next;
		if (i == chose)
            chosen = drawn;
	} 
    Move1Card(deadwood, drawn, 1);
    Move1Card(deadwood, drawn, 1);
    
    // return chosen card
    return  *chosen;
    
}


//Black Jack
//能力：在抽牌階段，必須亮出抽出的第二張牌，若該牌是紅心或方塊，他可以再多抽一張牌

void _Blackjack_ (Player player, card *deck){
    printf("The second card Blackjack drawn is:");
    print(gettail(player.CardinHand));
    if (gettail(player.CardinHand)->suit == "HEART"
     || gettail(player.CardinHand)->suit == "DIAMOND")
        draw(player.CardinHand,deck, 1);

}

//Jesse Jones
//能力：在抽牌階段時，第一張牌可以選擇從遊戲牌堆中或是任一位玩家的手牌中抽牌。
//第二張則是從遊戲牌中抽牌。

void _JesseJones_ (Player playerAs, card *deck, Player allPlayer[4], Character allCharacter[4], int isDead[4]){
    int tmp;
    int list[3] = {0};
    printf("Which deck do you want to draw from?\n\n\"1\" Deck \"2\" Player");
    scanf("%d", &tmp);
    if (tmp == 1)
        draw (playerAs.CardinHand,deck, 1);
    else{

        printf("Which Player's hand do you want to draw from?\n\n");
        for(int i=0; i< 3; i++){
            if (i == playerAs.id || isDead[i] == 1)
                continue;
            printf("\"%d\" Player%d (as %s)", i+1, allPlayer[i].id, allCharacter[i].name);
            list[i] = 1;
        }
        printf("\n");
        scanf("%d", &tmp);
        while (!check(tmp, list)){
            printf("Please enter a valid choice!\n");
            scanf("%d", &tmp);
            if (check(tmp, list)){
                draw(playerAs.CardinHand, allPlayer[tmp].CardinHand, 1);
                break;
            }
        }
    }
}

//Kit Carlson
//能力：抽牌階段時，可以從遊戲牌堆上方拿三張起來看，選擇兩張，放回一張到遊戲牌堆頂端。

void _KitCarlson_(Player player, card *deck) {
    
    int chose;
    int list[3];
    card *drawn;
    draw(drawn, deck, 3);
    printf("Which do you want to **put back** in deck?\n\n");
    for (int i=0;i<3;i++){
		drawn = drawn->next;
		printf("\"%d\" %s ", i+1, drawn->name);
        list[i] == 1;
	} 
    printf("\n");
    scanf("%d", &chose);
    while (!check(chose, list)){
            printf("Please enter a valid choice!\n");
            scanf("%d", &chose);
            if (check(chose, list)){
                //Pick one card back to deck
                Move1Card(deck, player.CardinHand, chose);
                //Put the rest to hand
                Move1Card(player.CardinHand, drawn, 1);
                Move1Card(player.CardinHand, drawn, 1);
                break;
            }
        }    
}

//Pedro Ramirez
//能力：在抽牌階段時，第一張牌可以選擇從棄牌堆或遊戲牌堆中抽牌，
//第二張牌只能從遊戲牌中抽牌。
void _PedroRamirez_(Player playerAs, card *deck, card *deadwood){
    
    int tmp;

    printf("Which deck do you want to draw from?\n\n\"1\" Deck \"2\" Deadwood");
    scanf("%d", &tmp);
    while (tmp != 1 || tmp != 2){
        printf("Please enter a valid choice!\n");
        scanf("%d", &tmp);
    }
    if (tmp == 1)
        draw(playerAs.CardinHand, deck, 1);
    if (tmp == 2)
        draw(playerAs.CardinHand, deadwood, 1);
            
}

