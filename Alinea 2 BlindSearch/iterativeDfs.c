#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "state.h"
#include "stateLinkedList.h"
#include "integerLinkedList.h"
#include "extraFunctions.h"

void solve(Memory *mem);
void initiateStack(SList *l, PointMemory *pMem, int iLim, int nRec);

//global variable
int generation = 2;

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

      /* this way of defining the generation gives better results
	 given that its useless to search for a solution that dosen't
	 have a minimum length, because there is not such solution */
      generation = mem->rMemMaxSize/3 + (mem->rMemMaxSize%3==0 ? 0: 1);
      
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
  
  while ( l->size > 0 )
    {
      cur = popState(l);
      updatePath(path, cur->index);

      if ( cur->seen==mem->rMemMaxSize )
	{	  
	  bestPath(sol, path);
	  break;
	}
      
      else if ( cur->g < generation )
  	for( int i=cur->index+1; i<mem->pMemSize; i++ )
  	  pushState(l, newState(mem->pMem, i, cur, cur->iLim));

      freeState(cur);
    }

  freeStateList(l);
  freeIntegerList(path);
  
  if ( sol->size!=0 )
    {
      printPath(mem->pMem, sol);
      freeIntegerList(sol);
    }
  
  else
    {
      freeIntegerList(sol);
      
      generation++;
      solve(mem);
    }
}

void initiateStack(SList *l, PointMemory *pMem, int iLim, int nRec)
{
  for( int i=0; i<iLim; i++ )
    pushState(l, newState(pMem, i, NULL, nRec));
}
