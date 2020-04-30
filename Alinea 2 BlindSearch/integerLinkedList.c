#include "integerLinkedList.h"
#define INVALID 2147483648

IList *newIntegerList()
{
  IList *l = (IList*)malloc(sizeof(IList));

  if ( l==NULL )
    errorMessageMem("initiateIntegerList");

  l->size = 0;
  
  l->first = newIntegerNode(INVALID);
  l->last = newIntegerNode(INVALID);
  
  l->first->next = l->last;
  l->first->prev = NULL;
  
  l->last->prev = l->first;
  l->last->next = NULL;
  
  return l;
}

INode *newIntegerNode(int a)
{
  INode *n = (INode*)malloc(sizeof(INode));

  if ( n==NULL )
    errorMessageMem("newIntegerNode");
  
  n->prev = NULL;
  n->next = NULL;

  n->value =  a;

  return n;
}

void insertIntegerFirst(IList *l, int n)
{
  INode *temp = newIntegerNode(n);
  
  temp->prev = l->first;
  temp->next = l->first->next;

  l->first->next->prev = temp;
  l->first->next = temp;

  l->size++;
}

void pushInteger(IList *l, int n) { insertIntegerFirst(l, n); }


void insertIntegerLast(IList *l, int n)
{
  INode *temp = newIntegerNode(n);
  
  temp->next = l->last;
  temp->prev = l->last->prev;

  l->last->prev->next = temp;
  l->last->prev = temp;

  l->size++;
}

void enqueueInteger(IList *l, int n) { insertIntegerLast(l, n); }


int removeFirstInteger(IList *l)
{
  if ( !l->size )
    return INVALID;

  INode *temp = l->first->next;

  if ( temp==l->last )
    errorMessageMem("removeFirst");
  
  temp->next->prev = l->first;
  l->first->next = temp->next;

  l->size--;

  int v = temp->value;

  free(temp);
  
  return v;
}

int popInteger(IList *l) { return removeFirstInteger(l); }

int dequeueInteger(IList *l) { return removeFirstInteger(l); }


int removeLastInteger(IList *l)
{
  if ( !l->size )
    return INVALID;

  INode *temp = l->last->prev;

  if ( temp==l->first )
    errorMessageMem("removeLast");
  
  temp->prev->next = l->last;
  l->last->prev = temp->prev;

  l->size--;

  return temp->value;
}

void removeInteger(IList *l, int v)
{
  INode *cur;
  
  for( cur = l->first->next; cur!=l->last && cur->value!=v; cur = cur->next );

  if ( cur==l->last )
    return;

  cur->next->prev = cur->prev;
  cur->prev->next = cur->next;

  l->size--;
}

int integerListSize(IList *l)
{
  if ( l->size<0 )
    errorMessageIllegalSize("IListSize");
  
  return l->size;
};

int getFirstInteger(IList *l)
{
  if ( l->size==0 )
    return INVALID;

  return l->first->next->value;
}

int topInteger(IList *l) { return getFirstInteger(l); }


int getLastInteger(IList *l)
{
  if ( l->size==0 )
    return INVALID;

  return l->last->prev->value;
}

int searchIntegerList(IList *l, int v)
{
  for( INode *cur = l->first->next; cur!=l->last; cur = cur->next )
    if ( cur->value == v )
      return 1;

  return 0;
}

void printIntegerList(IList *l)
{
  printf("IList size = %d\n", l->size);

  printf("Its Members are\n");

  if ( l->size==0 )
    printf("None\n");

  else
    {
      int i=0;
      
      for( INode *cur = l->first->next; cur!=l->last; cur = cur->next )
	{
	  printf("Index = %d\n", i++);
	  printf("Value = %d\n", cur->value);
	}
    }
}

void freeIntegerList(IList *l)
{
  if ( l==NULL )
    return;
  
  while ( l->size!=0 )
    dequeueInteger(l);
}
