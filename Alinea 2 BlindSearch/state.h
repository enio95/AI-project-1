#ifndef STATE
#define STATE

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "point.h"
#include "read.h"

/* idR -> Id of rectangles seen in the present state. Index is the
          identification of the rectangle 
	  idR[i]=0 means rec i has not been seen
          idR[i]>0 means rec i has been seen idR[i] times
   iLim -> size of idR. Usefull in some functions
   index -> Index of the last point seen
   pai -> Pointer to its father
   g -> path cost or size of path
   h -> under estimate of the cost to reach our goal
   f -> f=g+h its our under estimate of our path cost if we reach a sol
   seen -> Numeber of different rectangles present in the state*/
typedef struct State
{
  int *idR; 

  int iLim; 
  
  int index; 

  struct State *pai; 

  int g, h, f;

  int seen, sum;
  
}State;

State *newState(PointMemory *pMem, int index, State *pai, int nRec);
State *copyState(State *prev);

void copyIntArray(int *arr, int *vec, int iLim);
void getNewRectangles(int *arr, int *vec, int iLim);
void calculateSeen(State *state, int iLim);

void freeState(State *state);
void freeStateIdR(State *state);

void printState(State *state);
void printIntArray(int *arr, int iLim);
  
#endif
