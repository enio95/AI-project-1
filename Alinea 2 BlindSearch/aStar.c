#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "state.h"
#include "extraFunctions.h"
#include "heap.h"
#include "stateArray.h"

void solve(Memory *mem);
void initiateHeap(StateArray *arr, Memory *mem, Heap *h);

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
  
  Heap *h = newHeap();
  initiateHeap(arr, mem, h);

  int index;
  State *cur;
  
  while ( !heapIsEmpty(h) )
    {
      index = extractFromHeap(h);
      cur = &arr->state[index];

      if ( cur->seen==mem->rMemMaxSize )
	break;

      else
	for( int i=cur->index+1; i<mem->pMemSize; i++ )
	  {
	    int ind = arr->size;
	    
	    addToStateArray(arr, newState(mem->pMem, i, cur, mem->rMemMaxSize));
	    insertInHeap(h, ind, arr->state[ind].f);			    
	  }

      //these lines are here to improve memory efficiency and to run faster
      free(cur->idR);
      cur->idR=NULL;	  
    }

  printPath2(mem->pMem, cur, 0);
  
  destroyHeap(h);
  freeStateArray(arr);
}

void initiateHeap(StateArray *arr, Memory *mem, Heap *h)
{
  for( int i=0; i<mem->pMemSize; i++ )
    {
      addToStateArray(arr, newState(mem->pMem, i, NULL, mem->rMemMaxSize));
      insertInHeap(h, i, arr->state[i].f);
    }
}
