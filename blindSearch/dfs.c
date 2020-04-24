#include "errorMessage.c"
#include "read.c"
#include "object.c"
#include "listObj.c"
#include "extraFunctions.c"

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

      saveMemory(cur);
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
