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
    printf("Which deck do you want to draw from?\n\"1\" Deck\n\"2\" Player\n");
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
    printf("Which do you want to **put back** in deck?\n");
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

    printf("Which deck do you want to draw from?\n\"1\" Deck\n\"2\" Deadwood\n");
    scanf("%d", &tmp);
    while (tmp != 1 && tmp != 2){
        printf("Please enter a valid choice!\n");
        scanf("%d", &tmp);
    }
    if (tmp == 1)
        draw(playerAs.CardinHand, deck, 1);
    if (tmp == 2)
        draw(playerAs.CardinHand, deadwood, 1);
            
}

/*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "board.h"
#include "player.h"
#include "card.h"
#include "character.h"
#include "ability.h"

#include <stdbool.h>

int check(int i, int list[3]){
    if (i > 3 || i < 0)
        return 0;  
    if (list[i] == 1)
        return 1;
    return 0;      
}

//Bart Cassidy
//能力：被扣一滴血時，可以從卡牌堆中抽一張牌

void _BartCassidy_(Player player, card *deck) {
    
    draw(player.CardinHand,deck, 1);
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



//Calamity Janet
//能力：遊戲牌中的【閃躲】可以當【Bang】用；【Bang】也可以當【閃躲】用。
//當【閃躲】當【Bang】用時，還是必須遵守只能出一張砰的規則。

char _CalamityJanet_ (Player player, char cardToChoose, card *deadwood){

    if (strncmp(cardToChoose, "MISSED", 6) || strncmp(cardToChoose, "BANG", 4)){
        int tmp;
        printf("Which card do you want to use it as?\n\n\"1\" BANG \"2\"MISSED\n");
        scanf("%d", &tmp);
        if (tmp == 1){
            return "BANG";
        }else{  
            return "MISSED";
        }
      
    }
    return NULL;
   

}

//El Gringo
//能力：當被任一位玩家傷害時，每扣一滴血，就可以從該玩家隨機抽一張手牌。
//兩滴血就抽兩張，以此類推。炸彈造成的傷害無法發動此能力。

void _ElGringo_(Player player_Hurt, Player player_Offense, int cardChose) {
    
    Move1Card(player_Hurt.CardinHand,player_Offense.CardinHand, cardChose);
}

//Jesse Jones
//能力：在抽牌階段時，第一張牌可以選擇從遊戲牌堆中或是任一位玩家的手牌中抽牌。
//第二張則是從遊戲牌中抽牌。


void _JesseJones_ (Player playerAs, card *deck, Player allPlayer[4], Character allCharacter[4], int isDead[4]){

    
    int tmp;
    int list[3] = {0};
    printf("Which deck do you want to draw from?\n\n[1] Deck [2]Player");
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

///////////////////////////////// IN MAIN //////////////////////////////////////////
//Jourdonnais                                                                     //
//能力：內建【酒桶】功能，當被【Bang】時，可以從遊戲牌堆抽一張牌，                   //
//若是紅心則可以當作【閃躲】。若此角色裝備另一個【酒桶】，則可以有兩次抽牌機會。      //
////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////// IN MAIN ///////////////////////////////////////////
//Paul Regret                                                                     //
//能力：其他玩家看他的距離+1。他仍然可以再裝備【野馬】，裝備後距離共+2。             //
////////////////////////////////////////////////////////////////////////////////////

//Pedro Ramirez
//能力：在抽牌階段時，第一張牌可以選擇從棄牌堆或遊戲牌堆中抽牌，
//第二張牌只能從遊戲牌中抽牌。
void _PedroRamirez_ (Player playerAs, card *deck, card *deadwood){
    
    int tmp;

    printf("Which deck do you want to draw from?\n\n\"1\" Deck \"2\" Deadwood");
    scanf("%d", &tmp);
    while (tmp != 1 && tmp != 2){
        printf("Please enter a valid choice!\n");
        scanf("%d", &tmp);
    }
    if (tmp == 1)
        draw (playerAs.CardinHand, deck, 1);
    if (tmp == 2)
        draw (playerAs.CardinHand, deadwood, 1);
            
}

//////////////////////////////// IN MAIN ///////////////////////////////////////////
//Rose Doolan                                                                     //
//能力：看別的玩家的距離-1。他仍然可以裝備【瞄準器】，裝備後看其他玩家距離-2。       //
////////////////////////////////////////////////////////////////////////////////////

//Sid Ketchum
//能力：任何時刻都可以丟棄兩張卡牌，替自己補一滴血，且次數不限。


void _SidKetchum_(Player player, card *deadwood, Board board[4]) {

    Move1Card(deadwood, gettail(player.CardinHand), 2);
    board[player.id].hp++;

}

//Slab the Killer
//能力：其他玩家要躲過他出的【Bang】必須出兩張【閃躲】。
//如果其他人的【酒桶】成功觸發躲過時，只算一次【閃躲】，
//還需要再出一張【閃躲】才能真正躲過他的【Bang】。

int _SlabTheKiller_(Player playerOffense, Player PlayerHurt, card *HurtPlayerCardinHand) {
    
    if(FindCard(HurtPlayerCardinHand, "MISSED")){
        printf("They missed!\n");
        printf("But wait! Here comes another shot!\n");
        if(FindCard(HurtPlayerCardinHand, "MISSED")){
            return 1;
        }else{
            return 0;
        }
    }
        
    return 0;
}

//Suzy Lafayette
//能力：沒手牌時，可以立即從遊戲牌庫頂抽一張牌。

void _SuzyLafayette_(Player player, card *deck) {
    if (player.CardinHand == NULL){
        draw(player.CardinHand, deck, 1);
    }
}
*/
/*
//Vulture Sam
//能力：當一位玩家死亡時，接收該死亡玩家的手牌和場上的【裝備牌】到自己的手牌中。

void _VultureSam_(Player playerAs, Player playerDead, card *set[4], Board board[4]) {
    while(playerDead.CardinHand != NULL){
        Move1Card (playerAs.CardinHand, playerDead.CardinHand, 1);
    }
    //card set[4] = {/*Scope Card*///, /*Barrel Card*/, /*Jail Card*/, /*Bomb Card*///};
    //if (board[playerDead.id].isScope)
      //  Move1Card (playerAs.CardinHand, set[0], 0); //*Scope Card*
    //if (board[playerDead.id].isBarrel)
      //  Move1Card (playerAs.CardinHand, set[1], 1); //*Barrel Card*
	//if (board[playerDead.id].isJail)
//        Move1Card (playerAs.CardinHand, set[2], 2); //Jail Card
  //  if (board[playerDead.id].isBomb)
    //    Move1Card (playerAs.CardinHand, set[3], 3); //Bomb Card
            
      
//}

/////////////////////////////////////IN MAIN////////////////////////////////////////
//Willy the Kid                                                                   //
//能力：在他的回合，出【Bang】的張數沒有限制。                                      //
////////////////////////////////////////////////////////////////////////////////////

