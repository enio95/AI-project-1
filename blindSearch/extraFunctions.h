#ifndef EXTRA
#define EXTRA

#ifndef ERROR
#include "errorMessage.c"
#endif

int reachedGoal(Object *cur);
void updatePath(list *path, int index);
void printPath(Memory *mem, list *path);
void printPath1(Memory *mem, Object *cur);
void possibleSolution(list *sol, list *path);

#endif
