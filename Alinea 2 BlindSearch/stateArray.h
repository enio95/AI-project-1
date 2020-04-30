#ifndef STATEARRAY
#define STATEARRAY

#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "error.h"

typedef struct StateArray
{
  State *state;

  int size, maxSize;
  
}StateArray;

StateArray *newStateArray();
void addToStateArray(StateArray *arr, State *state);
void freeStateArray(StateArray *arr);
void printStateArray(StateArray *arr);

#endif
