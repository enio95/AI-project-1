#ifndef EXTRAFUNCTIONS
#define EXTRAFUNCTIONS

#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "point.h"
#include "state.h"
#include "integerLinkedList.h"


int isSolution(State *state);
void updatePath(IList *path, int index);
void bestPath(IList *sol, IList *path);

State *randomSolution(Memory *mem, char *seen);
int pickRandomPoint(PointMemory *pMem, char *seen, int iLim);
void moveIndexLeft(int *index, int iLim);

void printPath(PointMemory *pMem, IList *path);
void printPath1(PointMemory *pMem, IList *path);
void printPath2(PointMemory *pMem, State *cur, int i);
void printSolution(PointMemory *pMem, char *seen, int iLim);

int feasible(State *state, PointMemory *pMem, int index, char *seen); 
State *takePoint(State *state, PointMemory *pMem, int index);

#endif
