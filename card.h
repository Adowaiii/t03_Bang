#include"board.h"
#ifndef _CARD_H_
#define _CARD_H_

typedef struct Card{
	char suit[20];
	int number;
	char type[20];
	char name[20];
	char ability[20];
	int (*func)(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
	struct Card *next;
	}card;
	
int BANG(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int GATLING(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int INDIANS(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int PANIC(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int CATBALOU(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int STAGECOACH(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int WELLSFARGO(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int BEER(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int SALOON(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
int DUEL(Board board[],struct Card *set[],int user,int enemy,struct Card *deck,struct Card *deadwood,int number);
void draw(card *to,card *from,int number);
void CreateCard(card *pointer);
void Move1Card(card *to,card *from,int number);
int countCard(card *set);
int FindCard(card *set,char *input);
void print(card *set); 
void hurt(Board *player,int damage);
bool isMISSED(struct Card *set[],int user);
card *gettail(card *from);

#endif

