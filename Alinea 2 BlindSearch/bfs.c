#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "state.h"
#include "stateArray.h"
#include "extraFunctions.h"
#include "integerLinkedList.h"

void solve(Memory *mem);
void initiateQueue(StateArray *arr, Memory *mem, IList *q);

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
  StateArray *arr = newStateArray();

  IList *q = newIntegerList();
  initiateQueue(arr, mem, q);

  int index;
  State *cur;

  while ( q->size>0 )
    {
      index = dequeueInteger(q);
      cur = &arr->state[index];

      if ( cur->seen==mem->rMemMaxSize )
	break;

      else
	for( int i=cur->index+1; i<mem->pMemSize; i++ )
	  {
	    int ind = arr->size;

	    addToStateArray(arr, newState(mem->pMem, i, cur, mem->rMemMaxSize));
	    enqueueInteger(q, ind);	    
	  }

      //these lines are here to improve memory efficiency and to run faster
      free(cur->idR);
      cur->idR=NULL;      
    }
  
  printPath2(mem->pMem, cur, 0);

  freeIntegerList(q);
  freeStateArray(arr);
}

void initiateQueue(StateArray *arr, Memory *mem, IList *q)
{
  for( int i=0; i<mem->pMemSize; i++ )
    {
      addToStateArray(arr, newState(mem->pMem, i, NULL, mem->rMemMaxSize));
      enqueueInteger(q, i);
    }
}
