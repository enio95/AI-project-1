#include "errorMessage.c"
#include "read.c"
#include "object.c"
#include "listObj.c"
#include "list.c"
#include "extraFunctions.c"

void solve(Memory *mem);
void initiateQueue(List *l, Memory *m);

int main()
{
  int n;
  scanf("%d", &n);
  
  for( int i=0; i<n; i++ )
    {
      Memory *mem = newMemory();
      
      readInput(mem);
      
      solve(mem);

      freeMemory(mem);
    }
  
  return 0;
}

void solve(Memory *mem)
{
  List *l = newObjectList();

  initiateQueue(l, mem);
  
  Object *cur, *sol=NULL;

  while ( objectListSize(l)!=0 )
    {
      cur = popObject(l);
      
      if ( reachedGoal(cur) )
        sol = sol==NULL || sol->g > cur->g ? cur: sol;
      
      else
	  for( int i=cur->index+1; i<memSize; i++ )
	    enqueueObject(l, newObject(mem, i, cur));

      free(cur->rec);
    }

  printPath1(mem, sol);
  
  free(l);
}

void initiateQueue(List *l, Memory *mem)
{
  for( int i=0; i<memSize; i++ )
    enqueueObject(l, newObject(mem, i, NULL));
}
