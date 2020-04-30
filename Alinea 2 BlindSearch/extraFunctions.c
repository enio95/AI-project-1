#include "extraFunctions.h"

int isSolution(State *state)
{
  for( int i=1; i<=state->iLim; i++ )
    if ( state->idR[i]==0 )
      return 0;

  return 1;
}

void updatePath(IList *path, int index)
{
  while ( path->size>0 && topInteger(path) > index )
    popInteger(path);

  pushInteger(path, index);  
}

void bestPath(IList *sol, IList *path)
{
  if ( sol->size==0 || sol->size > path->size )
    {
      while ( sol->size>0 )
	dequeueInteger(sol);
      
      for( INode *cur = path->first->next; cur!=path->last; cur=cur->next )
	enqueueInteger(sol, cur->value);
    }
}

// print path while destroying
void printPath(PointMemory *pMem, IList *path)
{
  int temp = path->size;

  while ( path->size>0 )
    printPoint(pMem[popInteger(path)].p);

  printf("size = %d\nEND\n\n", temp);
}

// print path without destroying
void printPath1(PointMemory *pMem, IList *path)
{
  int temp = path->size;

  for( INode *cur = path->first->next; cur!=path->last; cur=cur->next )
    printPoint(pMem[cur->value].p);
  
  printf("size = %d\nEND\n\n", temp);
}

// print path from son to father untill we reach null
void printPath2(PointMemory *pMem, State *cur, int i)
{
  if ( cur==NULL )
    {
      printf("Size = %d\nEND\n\n", i);
      return;
    }
       
  printPoint(pMem[cur->index].p);

  printPath2(pMem, cur->pai, i+1);
}
