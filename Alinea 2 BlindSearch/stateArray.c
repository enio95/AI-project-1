#include "stateArray.h"

StateArray *newStateArray()
{
  StateArray *arr = (StateArray *)calloc(1, sizeof(StateArray));

  if ( arr==NULL )
    errorMessageMem("newStateArray");

  arr->size = 0;
  arr->maxSize = 10000000;

  arr->state = (State *)calloc(arr->maxSize, sizeof(State));

  if ( arr->state==NULL )
    errorMessageMem("newStateArray");

  return arr;
}

void addToStateArray(StateArray *arr, State *state)
{
  if ( arr->size == arr->maxSize )
    errorMessageMaxCapacity("addToStateArray");

  State *temp = &arr->state[arr->size];

  temp->index = state->index;
  temp->seen = state->seen;
  temp->iLim = state->iLim;
  temp->idR = state->idR;
  temp->pai = state->pai;
  temp->g = state->g;
  temp->h = state->h;
  temp->f = state->f;

  arr->size++;

  free(state);
}

void freeStateArray(StateArray *arr)
{
  for( int i=0; i<arr->size; i++ )
    if ( arr->state[i].idR!=NULL )
      free(arr->state[i].idR);

  free(arr->state);
  free(arr);
}

void printStateArray(StateArray *arr)
{
  printf("StateArray size = %d\n", arr->size);

  for( int i=0; i<arr->size; i++ )
    {
      printf("Position Index = %d\n", i);
      printState(&arr->state[i]);
    }
}
