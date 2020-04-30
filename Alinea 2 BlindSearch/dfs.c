#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "state.h"
#include "stateLinkedList.h"
#include "integerLinkedList.h"
#include "extraFunctions.h"

void solve(Memory *mem);
void initiateStack(SList *l, PointMemory *pMem, int iLim, int nRec);

int main()
{
  int wrSize;
  scanf("%d", &wrSize);

  for( int i=0;i<wrSize; i++ )
    {
      int caseSize;
      scanf("%d", &caseSize);
      
      Memory *mem = newMemory(caseSize);      
      readInput(mem, caseSize);

      printf("Case %d:\n", i+1);
      
      solve(mem);
      
      freeMemory(mem);      
    }
  
  return 0;
}

void solve(Memory *mem)
{
  SList *l = newStateList();
  initiateStack(l, mem->pMem, mem->pMemSize, mem->rMemMaxSize);

  IList *path = newIntegerList();
  IList *sol = newIntegerList();

  State *cur;

  int minPath = mem->rMemMaxSize/3 + (mem->rMemMaxSize%3==0 ? 0: 1);
  
  while ( l->size > 0 )
    {
      cur = popState(l);
      updatePath(path, cur->index);

      if ( isSolution(cur) )
  	{
  	  bestPath(sol, path);
	  
  	  // This condition improves overall perfomance 
  	  if ( sol->size <= minPath )
  	    break;
  	}

      else
  	for( int i=cur->index+1; i<mem->pMemSize; i++ )
  	  pushState(l, newState(mem->pMem, i, cur, cur->iLim));

      freeState(cur);
    }
  
  printPath(mem->pMem, sol);
  
  freeStateList(l);
  freeIntegerList(sol);
  freeIntegerList(path);
}

void initiateStack(SList *l, PointMemory *pMem, int iLim, int nRec)
{
  for( int i=0; i<iLim; i++ )
    pushState(l, newState(pMem, i, NULL, nRec));
}
