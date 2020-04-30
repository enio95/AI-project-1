#include "state.h"

State *newState(PointMemory *pMem, int index, State *pai, int nRec)
{
  State *state = (State *)calloc(1, sizeof(State));

  if ( state==NULL )
    errorMessageMem("newState");

  state->iLim = nRec;
  
  state->index = index;

  state->pai = pai;

  state->g = pai==NULL ? 1: pai->g + 1;

  state->idR = (int *)calloc(nRec+1, sizeof(int));

  if ( state->idR==NULL )
    errorMessageMem("newState");

  if ( pai!=NULL )
   copyIntArray(state->idR, pai->idR, nRec);

  getNewRectangles(state->idR, pMem[index].idR, 3);

  calculateSeen(state, nRec);

  int temp = nRec - state->seen;
 
  state->h = temp/3 + (temp%3==0 ? 0: 1);
  
  state->f = state->g + state->h;

  return state;
}

void copyIntArray(int *arr, int *vec, int iLim)
{
  for( int i=1; i<=iLim; i++ )
    arr[i] = vec[i];
}

void getNewRectangles(int *arr, int *vec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    arr[vec[i]]++;
}

void calculateSeen(State *state, int iLim)
{
  for( int i=1; i<=iLim; i++ )
    if ( state->idR[i] )
      state->seen++;
}

void freeState(State *state)
{
  freeStateIdR(state);
  free(state);
  state=NULL;
}

void freeStateIdR(State *state)
{
  if ( state->idR!=NULL )
    {
      free(state->idR);
      state->idR=NULL;
    }
}

void printState(State *state)
{
  printf("Point index = %d\n", state->index);

  printf("Rectangles seen = %d\n", state->seen);
  printf("g=%d, h=%d, f=%d\n", state->g, state->h, state->f);
  
  printIntArray(state->idR, state->iLim);

  printf("\n");
}

void printIntArray(int *arr, int iLim)
{
  printf("{");
  
  for( int i=1; i<=iLim; i++ )
    {
      printf("ID=%d:Seen=%d", i, arr[i]);

      if ( i<iLim )
	printf(", ");
    }

  printf("}\n");
}

