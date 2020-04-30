#include "stateLinkedList.h"

SList *newStateList()
{
  SList *l = (SList*)malloc(sizeof(SList));

  if ( l==NULL )
    errorMessageMem("initiateList");

  l->size = 0;
  
  l->first = newStateNode(NULL);
  l->last = newStateNode(NULL);
  
  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

SNode *newStateNode(State *state)
{
  SNode *n = (SNode*)malloc(sizeof(SNode));

  if ( n==NULL )
    errorMessageMem("newStateNode");
  
  n->prev = NULL;
  n->next = NULL;

  n->state =  state;

  return n;
}

void insertStateFirst(SList *l, State *state)
{
  SNode *temp = newStateNode(state);
  
  temp->prev = l->first;
  temp->next = l->first->next;

  l->first->next->prev = temp;
  l->first->next = temp;

  l->size++;
}

void pushState(SList *l, State *state) { insertStateFirst(l, state); }


void insertStateLast(SList *l, State *state)
{
  SNode *temp = newStateNode(state);
  
  temp->next = l->last;
  temp->prev = l->last->prev;

  l->last->prev->next = temp;
  l->last->prev = temp;

  l->size++;
}

void enqueueState(SList *l, State *state) { insertStateLast(l, state); }


State *removeFirstState(SList *l)
{
  if ( !l->size )
    return NULL;

  SNode *temp = l->first->next;

  if ( temp==l->last )
    errorMessageListSize("removeFirstState");
  
  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  State *stateTemp = temp->state;

  free(temp);

  return stateTemp;
}

State *popState(SList *l) { return removeFirstState(l); }

State *dequeueState(SList *l) { return removeFirstState(l); }

int stateListSize(SList *l)
{
  if ( l->size<0 )
    errorMessageIllegalSize("stateListSize");
  
  return l->size;
};

void printStateList(SList *l)
{
  int i=0;
  
  for( SNode *cur = l->first->next; cur!=l->last; cur=cur->next, i++ )
    {
      printf("Index = %d\n", i);
      
      printState(cur->state);
    }
  
  putchar('\n');
}

void freeStateList(SList *l)
{
  while ( l->size>0 )
    freeState(dequeueState(l));
}
