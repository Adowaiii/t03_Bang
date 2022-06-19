#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#include"player.h"
#include"card.h"

#define and &&
#define or ||
#define PLAYER_NUM 4
	//抽牌堆 = deck
	//棄牌堆 = deadwood 

int countCard(card *set){
	int count = 0;
	card *pointer = set;
	while(pointer->next != NULL){
		count++;
		pointer = pointer->next;
	}
	return count;
}

void print(card *set){			//請填header 
	int count=0;
	card *pointer = set;
	if(pointer->next == NULL){
		printf("empty\n");
	}
	while(pointer->next != NULL){
		count++;
		pointer = pointer->next;
		printf("[%d]%15s %7s %2d\n",count,pointer->name,pointer->suit,pointer->number);
	}
}

void Move1Card(card *to,card *from,int number){			//牌堆不能為空!!! 
	card *pointer = from;
	for(int i=0;i<number-1;i++){
		pointer = pointer->next;
	}
	card *tail = gettail(to);
	tail->next = pointer->next;
	tail = tail->next;
	pointer->next = tail->next;
	tail->next = NULL;
	printf("Moved\n");
}

card *gettail(card *from){
	card *pointer = from;
	while(pointer->next != NULL){
		pointer = pointer->next;
	}
	//printf("%15s %7s %2d\n",pointer->name,pointer->suit,pointer->number);
	//printf("gettailed\n");
	return pointer;
}

void draw(card *to,card *from,int number){
	card *pointer;
	card *tail;
	tail = gettail(to);
	for(int i=0;i<number;i++){
		tail->next = from->next;
		tail = tail->next;
		from->next = tail->next;
		tail->next = NULL;
	}
	printf("drawed\n");
}
int FindCard(card *set,char *input){
	int count=0;
	card *pointer = set;
	while(pointer->next != NULL){
		count++;
		pointer = pointer->next;
		if(strcmp(pointer->name,input) == 0){
			return count;
		} 
	}
	return -1;
}
//////////////////////////////////////////////////////////////////
void hurt(Board *player,int damage){
	player->hp -= damage;
}
bool UseOrNot(int user,char *input){
	int option = 1;
	printf("PLAYER[%d] Do You Want To Use %s? 1.YES 2.NO ...>",user,input);
	scanf("%d",&option);
	if(option == 1)
		return true;
	else
		return false;
}
int BANG(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	if(isMISSED(set,enemy)){
		Move1Card(deadwood,set[enemy],FindCard(set[enemy],"MISSED"));
	}
	else{
		hurt(&board[enemy],1);
	}
	Move1Card(deadwood,set[user],number);
}
bool isMISSED(struct Card *set[],int user){
	if(FindCard(set[user],"MISSED") != -1 and UseOrNot(user,"MISSED") == true){
		return true;
	}
	return false;	
}
int GATLING(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	for(int i=0;i<PLAYER_NUM;i++){
		if(isMISSED(set,i) and i != user){
			Move1Card(deadwood,set[i],FindCard(set[i],"MISSED"));
		}
		else{
			hurt(&board[i],1);
		}
	}
	Move1Card(deadwood,set[user],number);
}
int INDIANS(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	for(int i=0;i<PLAYER_NUM;i++){
		if(i != user){
			if(FindCard(set[i],"BANG") == -1){
				hurt(&board[i],1);
			}
			else{
				Move1Card(deadwood,set[i],FindCard(set[i],"BANG"));
			} 
		}
	}
	Move1Card(deadwood,set[user],number);
}
int PANIC(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	
	Move1Card(deadwood,set[user],number);
}
int CATBALOU(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	
	Move1Card(deadwood,set[user],number);
}
int STAGECOACH(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	draw(set[user],deck,2);
	Move1Card(deadwood,set[user],number);
}
int WELLSFARGO(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	draw(set[user],deck,3);
	Move1Card(deadwood,set[user],number);
}
int GENERALSTORE(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	Move1Card(deadwood,set[user],number);
	card *temp = malloc(sizeof(card));
	int input=1;
	draw(temp,deck,PLAYER_NUM);
	for(int i=0;i<PLAYER_NUM;i++){
		printf("PLAYER[%d] Which Card Do You Want To Keep?\n",user);
		print(temp);
		printf("...>");
		scanf("%d",&input);
		Move1Card(set[user],temp,input);
		if(user == 3){
			user = 0;
		}
		else{
			user++;
		}
	}
	free(temp);
}
int BEER(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	hurt(&board[user],-1);
	Move1Card(deadwood,set[user],number);
}
int SALOON(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	for(int i=0;i<4;i++){
		hurt(&board[i],-1);
	}
	Move1Card(deadwood,set[user],number);
}
int DUEL(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number){
	while(1){
		if(FindCard(set[enemy],"BANG") != -1){
			Move1Card(deadwood,set[enemy],FindCard(set[enemy],"BANG"));
			if(FindCard(set[user],"BANG") != -1){
				Move1Card(deadwood,set[user],FindCard(set[user],"BANG"));
			}
			else{
				hurt(&board[user],1);
				break;
			}
		}
		else{
			hurt(&board[enemy],1);
			break;
		}
	}
	Move1Card(deadwood,set[user],number);
}
void CreateCard(card *pointer){
	
	//BARREL 2
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"BARREL",20);
	strncpy(pointer->ability,"BARREL",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 12;
	strncpy(pointer->type,"equipment",20);
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"BARREL",20);
	strncpy(pointer->ability,"BARREL",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 13;
	strncpy(pointer->type,"equipment",20);//BARREL
	//SCOPE 1
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"SCOPE",20);
	strncpy(pointer->ability,"SCOPE",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 1;
	strncpy(pointer->type,"equipment",20);//SCOPE
	//MUSTANG 2
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"MUSTANG",20);
	strncpy(pointer->ability,"MUSTANG",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 8;
	strncpy(pointer->type,"equipment",20);
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"MUSTANG",20);
	strncpy(pointer->ability,"MUSTANG",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 9;
	strncpy(pointer->type,"equipment",20);//MUSTANG
	//JAIL 3
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"JAIL",20);
	strncpy(pointer->ability,"JAIL",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 4;
	strncpy(pointer->type,"equipment",20);
	for(int i=10;i<=11;i++){
		pointer->next = malloc(sizeof(card));
		pointer = pointer->next;
		strncpy(pointer->name,"JAIL",20);
		strncpy(pointer->ability,"JAIL",20);
		strncpy(pointer->suit,"SPADE",20);
		pointer->number = i;
		strncpy(pointer->type,"equipment",20);//JAIL
	}
	//DYNAMITE 1
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"DYNAMITE",20);
	strncpy(pointer->ability,"DYNAMITE",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 2;
	strncpy(pointer->type,"equipment",20);//DYNAMITE
	//VOLCANIC 2
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"VOLCANIC",20);
	strncpy(pointer->ability,"VOLCANIC",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 10;
	strncpy(pointer->type,"equipment",20);
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"VOLCANIC",20);
	strncpy(pointer->ability,"VOLCANIC",20);
	strncpy(pointer->suit,"CLUB",20);
	pointer->number = 10;
	strncpy(pointer->type,"equipment",20);//VOLCANIC
	//SCHOFIELD 3
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"SCHOFIELD",20);
	strncpy(pointer->ability,"SCHOFIELD",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 13;
	strncpy(pointer->type,"equipment",20);
	for(int i=11;i<=12;i++){
		pointer->next = malloc(sizeof(card));
		pointer = pointer->next;
		strncpy(pointer->name,"SCHOFIELD",20);
		strncpy(pointer->ability,"SCHOFIELD",20);
		strncpy(pointer->suit,"CLUB",20);
		pointer->number = i;
		strncpy(pointer->type,"equipment",20);//SCHOFIELD
	}
	//REMINGTON 1
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"REMINGTON",20);
	strncpy(pointer->ability,"REMINGTON",20);
	strncpy(pointer->suit,"CLUB",20);
	pointer->number = 13;
	strncpy(pointer->type,"equipment",20);//REMINGTON
	//REV.CARABINE 1
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"REV.CARABINE",20);
	strncpy(pointer->ability,"REV.CARABINE",20);
	strncpy(pointer->suit,"CLUB",20);
	pointer->number = 1;
	strncpy(pointer->type,"equipment",20);//REV.CARABINE
	//WINCHEDTER 1
	pointer->next = malloc(sizeof(card));
	pointer = pointer->next;
	strncpy(pointer->name,"WINCHEDTER",20);
	strncpy(pointer->ability,"WINCHEDTER",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 8;
	strncpy(pointer->type,"equipment",20);//WINCHEDTER
	//BANG 25
	pointer->next = malloc(sizeof(card));//BANG
	pointer = pointer->next;
	strncpy(pointer->name,"BANG",20);
	strncpy(pointer->ability,"BANG",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 1;
	pointer->func = &BANG;
	strncpy(pointer->type,"item",20);
	pointer->next = malloc(sizeof(card));//BANG
	pointer = pointer->next;
	strncpy(pointer->name,"BANG",20);
	strncpy(pointer->ability,"BANG",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 1;
	pointer->func = &BANG;
	strncpy(pointer->type,"item",20);
	for(int i=12;i<=13;i++){
		pointer->next = malloc(sizeof(card));//BANG
		pointer = pointer->next;
		strncpy(pointer->name,"BANG",20);
		strncpy(pointer->ability,"BANG",20);
		strncpy(pointer->suit,"HEART",20);
		pointer->number = i;
		pointer->func = &BANG;
		strncpy(pointer->type,"item",20);
	}
	for(int i=1;i<=13;i++){
		pointer->next = malloc(sizeof(card));//BANG
		pointer = pointer->next;
		strncpy(pointer->name,"BANG",20);
		strncpy(pointer->ability,"BANG",20);
		strncpy(pointer->suit,"DIAMOND",20);
		pointer->number = i;
		pointer->func = &BANG;
		strncpy(pointer->type,"item",20);
	}
	for(int i=2;i<=9;i++){
		pointer->next = malloc(sizeof(card));//BANG
		pointer = pointer->next;
		strncpy(pointer->name,"BANG",20);
		strncpy(pointer->ability,"BANG",20);
		strncpy(pointer->suit,"CLUB",20);
		pointer->number = i;
		pointer->func = &BANG;
		strncpy(pointer->type,"item",20);
	}
	//MISSED 12
	for(int i=2;i<=8;i++){
		pointer->next = malloc(sizeof(card));//MISSED
		pointer = pointer->next;
		strncpy(pointer->name,"MISSED",20);
		strncpy(pointer->ability,"MISSED",20);
		strncpy(pointer->suit,"SPADE",20);
		pointer->number = i;
		strncpy(pointer->type,"item",20);
	}
	for(int i=10;i<=13;i++){
		pointer->next = malloc(sizeof(card));//MISSED
		pointer = pointer->next;
		strncpy(pointer->name,"MISSED",20);
		strncpy(pointer->ability,"MISSED",20);
		strncpy(pointer->suit,"CLUB",20);
		pointer->number = i;
		strncpy(pointer->type,"item",20);
	}
	pointer->next = malloc(sizeof(card));//MISSED
	pointer = pointer->next;
	strncpy(pointer->name,"MISSED",20);
	strncpy(pointer->ability,"MISSED",20);
	strncpy(pointer->suit,"CLUB",20);
	pointer->number = 1;
	strncpy(pointer->type,"item",20);
	//GATLING 1
	pointer->next = malloc(sizeof(card));//GATLING
	pointer = pointer->next;
	strncpy(pointer->name,"GATLING",20);
	strncpy(pointer->ability,"GATLING",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 10;
	pointer->func = &GATLING;
	strncpy(pointer->type,"item",20);
	//INDIANS 1
	pointer->next = malloc(sizeof(card));//INDIANS
	pointer = pointer->next;
	strncpy(pointer->name,"INDIANS",20);
	strncpy(pointer->ability,"INDIANS",20);
	strncpy(pointer->suit,"DIAMOND",20);
	pointer->number = 13;
	pointer->func = &INDIANS;
	pointer->next = malloc(sizeof(card));//INDIANS
	pointer = pointer->next;
	strncpy(pointer->name,"INDIANS",20);
	strncpy(pointer->ability,"INDIANS",20);
	strncpy(pointer->suit,"DIAMOND",20);
	pointer->number = 1;
	pointer->func = &INDIANS;
	strncpy(pointer->type,"item",20);
	//PANIC 4
	pointer->next = malloc(sizeof(card));//PANIC
	pointer = pointer->next;
	strncpy(pointer->name,"PANIC",20);
	strncpy(pointer->ability,"PANIC",20);
	strncpy(pointer->suit,"DIAMOND",20);
	pointer->number = 8;
	pointer->func = &PANIC;
	strncpy(pointer->type,"item",20);
	pointer->next = malloc(sizeof(card));//PANIC
	pointer = pointer->next;
	strncpy(pointer->name,"PANIC",20);
	strncpy(pointer->ability,"PANIC",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 1;
	pointer->func = &PANIC;
	strncpy(pointer->type,"item",20);
	for(int i=11;i<=12;i++){
		pointer->next = malloc(sizeof(card));//PANIC
		pointer = pointer->next;
		strncpy(pointer->name,"PANIC",20);
		strncpy(pointer->ability,"PANIC",20);
		strncpy(pointer->suit,"HEART",20);
		pointer->number = i;
		pointer->func = &PANIC;
		strncpy(pointer->type,"item",20);
	}
	//CAT BALOU 4
	pointer->next = malloc(sizeof(card));//CAT BALOU
	pointer = pointer->next;
	strncpy(pointer->name,"CAT BALOU",20);
	strncpy(pointer->ability,"CAT BALOU",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 13;
	pointer->func = &CATBALOU;
	strncpy(pointer->type,"item",20);
	for(int i=9;i<=11;i++){
		pointer->next = malloc(sizeof(card));//CAT BALOU
		pointer = pointer->next;
		strncpy(pointer->name,"CAT BALOU",20);
		strncpy(pointer->ability,"CAT BALOU",20);
		strncpy(pointer->suit,"DIAMOND",20);
		pointer->number = i;
		pointer->func = &CATBALOU;
		strncpy(pointer->type,"item",20);
	}
	//STAGECOACH 2
	for(int i=1;i<=2;i++){
		pointer->next = malloc(sizeof(card));//STAGECOACH
		pointer = pointer->next;
		strncpy(pointer->name,"STAGECOACH",20);
		strncpy(pointer->ability,"STAGECOACH",20);
		strncpy(pointer->suit,"SPADE",20);
		pointer->number = 9;
		pointer->func = &STAGECOACH;
		strncpy(pointer->type,"item",20);
	}
	//WELLS FARGO 1
	pointer->next = malloc(sizeof(card));//WELLS FARGO
	pointer = pointer->next;
	strncpy(pointer->name,"WELLS FARGO",20);
	strncpy(pointer->ability,"WELLS FARGO",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 3;
	pointer->func = &WELLSFARGO;
	strncpy(pointer->type,"item",20);
	//GENERAL STORE 2
	pointer->next = malloc(sizeof(card));//GENERAL STORE
	pointer = pointer->next;
	strncpy(pointer->name,"GENERAL STORE",20);
	strncpy(pointer->ability,"GENERAL STORE",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 12;
	pointer->func = &GENERALSTORE;
	strncpy(pointer->type,"item",20);
	pointer->next = malloc(sizeof(card));//GENERAL STORE
	pointer = pointer->next;
	strncpy(pointer->name,"GENERAL STORE",20);
	strncpy(pointer->ability,"GENERAL STORE",20);
	strncpy(pointer->suit,"CLUB",20);
	pointer->number = 9;
	pointer->func = &GENERALSTORE;
	strncpy(pointer->type,"item",20);
	//BEER 6
	for(int i=6;i<=11;i++){
		pointer->next = malloc(sizeof(card));//BEER
		pointer = pointer->next;
		strncpy(pointer->name,"BEER",20);
		strncpy(pointer->ability,"BEER",20);
		strncpy(pointer->suit,"HEART",20);
		pointer->number = i;
		pointer->func = &BEER;
		strncpy(pointer->type,"item",20);
	}
	//SALOON 1
	pointer->next = malloc(sizeof(card));//SALOON
	pointer = pointer->next;
	strncpy(pointer->name,"SALOON",20);
	strncpy(pointer->ability,"SALOON",20);
	strncpy(pointer->suit,"HEART",20);
	pointer->number = 5;
	pointer->func = &SALOON;
	strncpy(pointer->type,"item",20);
	//DUEL 3
	pointer->next = malloc(sizeof(card));//DUEL
	pointer = pointer->next;
	strncpy(pointer->name,"DUEL",20);
	strncpy(pointer->ability,"DUEL",20);
	strncpy(pointer->suit,"SPADE",20);
	pointer->number = 11;
	pointer->func = &DUEL;
	strncpy(pointer->type,"item",20);
	pointer->next = malloc(sizeof(card));//DUEL
	pointer = pointer->next;
	strncpy(pointer->name,"DUEL",20);
	strncpy(pointer->ability,"DUEL",20);
	strncpy(pointer->suit,"DIAMOND",20);
	pointer->number = 12;
	pointer->func = &DUEL;
	strncpy(pointer->type,"item",20);
	pointer->next = malloc(sizeof(card));//DUEL
	pointer = pointer->next;
	strncpy(pointer->name,"DUEL",20);
	strncpy(pointer->ability,"DUEL",20);
	strncpy(pointer->suit,"CLUB",20);
	pointer->number = 8;
	pointer->func = &DUEL;
	strncpy(pointer->type,"item",20);
	pointer->next = NULL;
	printf("Card Created\n");
}