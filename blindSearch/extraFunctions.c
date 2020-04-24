#include "extraFunctions.h"


int reachedGoal(Object *obj)
{
  for( int i=1; i<=nRec; i++ )
    if ( !obj->rec[i] )
      return 0;

  return 1;
}

void potentialSol(Object *cur)
{
  optimalSolution = optimalSolution==NULL || pathSize(optimalSolution) > pathSize(cur) ? cur: optimalSolution;
}

int pathSize(Object *cur)
{
  if ( cur==NULL )
    return 0;

  else
    return 1 + pathSize(cur->pai);
}

void saveMemory(Object *obj)
{
  if ( obj==NULL )
    return;

  free(obj->rec);
}
