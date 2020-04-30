#ifndef INTEGERLINKEDLIST
#define INTEGERLINKEDLIST

#include <stdio.h>
#include <stdlib.h>

#include "errorMessage.h"

typedef struct INode
{
  int value;

  struct INode *prev, *next;
  
}INode;

typedef struct
{
  int size;

  struct INode *first, *last;
  
}IList;

IList *newIntegerList();
INode *newIntegerNode(int a);

void insertIntegerFirst(IList *l, int n);
void pushInteger(IList *l, int n);

void insertIntegerLast(IList *l, int n);
void enqueueInteger(IList *l, int n);

int removeFirstInteger(IList *l);
int popInteger(IList *l);
int dequeueInteger(IList *l);

int removeLastInteger(IList *l);

int integerListSize(IList *l);

int getFirstInteger(IList *l);
int topInteger(IList *l);

int getLastInteger(IList *l);

int searchIntegerList(IList *l, int v);

void printIntegerList(IList *l);

void freeIntegerList(IList *l);
  
#endif
