#include "errorMessage.c"
#include "read.c"
#include "object.c"
#include "listObj.c"

Object *optimalSolution = NULL;

void solve(Memory *mem);
void initiateList(List *l, Memory *m);

int reachedGoal(Object *cur);
void potentialSol(Object *cur);
int pathSize(Object *cur);

int main()
{
  int n;
  scanf("%d", &n);
  
  for( int i=0; i<n; i++ )
    {
      Memory *mem = newMemory();
      
      readInput(mem);
      
      //printMemory(mem);
      
      solve(mem);

      freeMemory(mem);
    }

  return 0;
}

void solve(Memory *mem)
{
  List *l = newObjectList();

  initiateList(l, mem);
  
  Object *cur;

  while ( objectListSize(l)!=0 )
    {
      cur = popObject(l);
      
      if ( reachedGoal(cur) )
	potentialSol(cur);
      
      else
	for( int i=1; cur->mem[i].p!=NULL; i++ )
	  pushObject(l, newObject(&cur->mem[i], cur));
    }

  printPath(optimalSolution);
  putchar('\n');
  free(l);
}

void initiateList(List *l, Memory *m)
{
  for ( int i=0; i<memSize; i++ )
      pushObject(l, newObject(&m[i], NULL));
}

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
