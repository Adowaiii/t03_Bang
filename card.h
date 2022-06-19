
#include "board.h"
#ifndef _CARD_H_
#define _CARD_H_

typedef struct Card{
	char suit[20];
	int number;
	char type[20];
	char name[20];
	char ability[20];
	int (*func)(Board,Board,int);
	struct Card *next;
	}card;
	
int BANG(Board,int,int);
int MISSED(int,int,int);
int GATLING(int,int,int);
int INDIANS(int,int,int);
int PANIC(int,int,int);
int CATBALOU(int,int,int);
int STAGECOACH(int,int,int);
int WELLSFARGO(int,int,int);
int BEER(int,int,int);
int SALOON(int,int,int);
int DUEL(int,int,int);
void draw(card *to,card *from,int number);
void CreateCard(card *pointer);
void Move1Card(card *to,card *from,int number);
void print(card *set); 
card *gettail(card *from);


#endif

