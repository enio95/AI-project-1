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
void printPath(PointMemory *pMem, IList *path);
void printPath1(PointMemory *pMem, IList *path);
void printPath2(PointMemory *pMem, State *cur, int i);

#endif
