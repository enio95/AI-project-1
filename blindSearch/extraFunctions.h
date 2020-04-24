#ifndef EXTRA
#define EXTRA

#ifndef ERROR
#include "errorMessage.c"
#endif

Object *optimalSolution = NULL;

int reachedGoal(Object *obj);
void potentialSol(Object *cur);
int pathSize(Object *cur);
void saveMemory(Object *obj);

#endif
