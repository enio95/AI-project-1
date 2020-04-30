#ifndef STATELINKEDLIST
#define STATELINKEDLIST

#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "errorMessage.h"

typedef struct SNode
{
  State *state;
  
  struct SNode *prev, *next;
  
}SNode;

typedef struct SList
{
  int size;

  struct SNode *first, *last;
  
}SList;

SList *newStateList();
SNode *newStateNode(State *state);

void insertStateFirst(SList *l, State *state);
void pushState(SList *l, State *state);

void insertStateLast(SList *l, State *state);
void enqueueState(SList *l, State *state);

State *removeFirstState(SList *l);
State *popState(SList *l);
State *dequeueState(SList *l);

int stateListSize(SList *l);

void printStateList(SList *l);

void freeStateList(SList *l);

#endif
