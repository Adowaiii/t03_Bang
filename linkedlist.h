#include <stdio.h>
#include <stdbool.h>

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


typedef struct{
    int id;
}Node;

typedef struct{
    Node node;
} LinkedList;

void LinkedList_Ctor(Node node, int Num);

// 獲取父類屬性宣告
bool isEmpty(LinkedList *this);
bool isFull(LinkedList *this);
void addNode(LinkedList *this);
void delNode(LinkedList *this);

#endif