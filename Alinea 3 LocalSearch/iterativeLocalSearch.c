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

State *ILS(Memory *mem, State *random, char *seen);
int findPointToPut(char *pointPushed, char *seen, int iLim);
State *moveAway(State *minSol, PointMemory *pMem, int index, int iLim);

void copyCharArray(char *arr, char *vec, int iLim);

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

      if ( seen==NULL )
	errorMessageMem("main");
      
      State *state = randomSolution(mem, seen);
      
      printf("Random\n");
      printSolution(mem->pMem, seen, mem->pMemSize);

      state = ILS(mem, state, seen);
      
      printf("Local Minimum\n");
      printSolution(mem->pMem, seen, mem->pMemSize);

      free(seen);
      freeState(state);
      freeMemory(mem);
    }
  
  return 0;
}

State *ILS(Memory *mem, State *random, char *seen)
{
  char *pointPushed = (char *)calloc(mem->pMemSize, sizeof(char));

  if ( pointPushed==NULL )
    errorMessageMem("ILS");

  State *minSol = findLocalMinimum(mem,random, seen);  

  State *cur = NULL;
  char curSeen[mem->pMemSize];
  
  int index = findPointToPut(pointPushed, seen, mem->pMemSize);

  while ( index>=0 )
    {
      copyCharArray(curSeen, seen, mem->pMemSize);
      
      pointPushed[index] = '1';
      curSeen[index] = '1';
      
      cur = moveAway(minSol, mem->pMem, index, mem->rMemMaxSize);
      
      cur = findLocalMinimum(mem, cur, curSeen);      

      if ( cur->g < minSol->g || ( cur->sum > minSol->sum && cur->g <= minSol->g ) )
	{
	  freeState(minSol);
	  
	  copyCharArray(seen, curSeen, mem->pMemSize);
	  minSol = cur;
	}

      else
	freeState(cur);

      index = findPointToPut(pointPushed, seen, mem->pMemSize);      
    }

  free(pointPushed);
 
  return minSol;
}

State *moveAway(State *minSol, PointMemory *pMem, int index, int iLim)
{
  return newState(pMem, index, minSol, iLim);
}

int findPointToPut(char *pointPushed, char *seen, int iLim)
{
  for( int i=0; i<iLim; i++ )
    if ( pointPushed[i]!='1' && seen[i]!='1' )
      return i;

  return -1;
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

void copyCharArray(char *arr, char *vec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    arr[i] = vec[i];		   
}
