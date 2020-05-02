#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "read.h"
#include "point.h"
#include "state.h"
#include "extraFunctions.h"

State *findLocalMinimum(Memory *mem, State *cur, char *seen);
int whichIsBest(PointMemory *pMem, State *state1, State *state2);
int countRepeted(PointMemory *pMem, State *state);


int main()
{
  srand(time(NULL));
  
  int wrSize;
  scanf("%d", &wrSize);

  for( int i=0;i<wrSize; i++ )
    {
      int caseSize;
      scanf("%d", &caseSize);
      
      Memory *mem = newMemory(caseSize);      
      readInput(mem, caseSize);
      
      printf("Case %d:\n", i+1);

      char *seen = (char *)calloc(mem->pMemSize, sizeof(char));
      
      State *state = randomSolution(mem, seen);
      
      printf("Random\n");
      printSolution(mem->pMem, seen, mem->pMemSize);

      state = findLocalMinimum(mem, state, seen);
      
      printf("Local Minimum\n");
      printSolution(mem->pMem, seen, mem->pMemSize);

      free(seen);
      freeState(state);
      freeMemory(mem);
    }
  
  return 0;
}

State *findLocalMinimum(Memory *mem, State *cur, char *seen)
{
  int delete;

  State *best = NULL;
  State *temp = NULL;
  
  for( int i=0; i<mem->pMemSize; i++ )
    if ( feasible(cur, mem->pMem, i, seen) )
      {
	temp = takePoint(cur, mem->pMem, i);

	if ( best==NULL )
	  {
	    best = temp;
	    delete = i;
	  }
	
	// >0 --> best é o melhor estado, <0 --> temp é o melhor estado
	else if ( whichIsBest(mem->pMem, best, temp) )
	  freeState(temp);

	else
	  {
	    freeState(best);
	    best = temp;
	    delete = i;
	  }
      }

  // ou seja encontrou algum estado vizinho melhor que cur
  if ( best!=NULL )
    {
      freeState(cur);

      seen[delete] = '0';
      
      return findLocalMinimum(mem, best, seen);
    }

  else
    return cur;
}

int whichIsBest(PointMemory *pMem, State *state1, State *state2)
{
  if ( state1->sum > state2->sum )
    return 1;

  else if ( state1->sum < state2->sum )
    return 0;

  else
    {
      int a = countRepeted(pMem, state1);
      int b = countRepeted(pMem, state2);

      return a-b;
    }
}

int countRepeted(PointMemory *pMem, State *state)
{
  int sum = 0, ind;

  for( int i=0; i<3; i++ )
    {
      ind = pMem[state->index].idR[i];

      if ( ind!=0 )
	sum += state->idR[ind];
    }

  return sum;
}
