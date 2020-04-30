#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "state.h"
#include "stateLinkedList.h"
#include "integerLinkedList.h"
#include "extraFunctions.h"

void solve(Memory *mem);
void initiateStack(SList *l, PointMemory *pMem, int iLim, int nRec);

//glboal variables
int lowerBound, upperBound;

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

      lowerBound = mem->rMemMaxSize/3 + (mem->rMemMaxSize%3==0 ? 0: 1);
      upperBound = mem->rMemMaxSize/2 + 1;
       
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
	  upperBound = upperBound>cur->g ? cur->g: upperBound;
	  
  	  // This condition improves overall perfomance 
  	  if ( sol->size <= lowerBound )
  	    break;
	}

      else if (  cur->f < upperBound )
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
	  
