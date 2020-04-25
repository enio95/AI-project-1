#include "errorMessage.c"
#include "read.c"
#include "object.c"
#include "listObj.c"
#include "list.c"
#include "extraFunctions.c"


void solve(Memory *mem);
void initiateStack(List *l, Memory *mem);
  
int main()
{
  int n;
  scanf("%d", &n);

  for ( int i=0; i<n; i++ )
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
  initiateStack(l, mem);

  list *path = newList();
  list *sol = newList();

  Object *cur;
  int lowerB = -1;
  
  while ( l->size > 0 )
    {
      cur = popObject(l);
      updatePath(path, cur->index);
      
      if ( reachedGoal(cur) )
	{
	  possibleSolution(sol, path);

	  lowerB = lowerB==-1 || lowerB > cur->g ? cur->g: lowerB;
	}
      
      else if ( ( lowerB!=-1 && cur->g < lowerB ) || lowerB==-1 )
	{
	  for( int i=cur->index+1; i<memSize; i++ )
	    pushObject(l, newObject(mem, i, cur));	    
	}

      freeObject(cur);
    }

  printPath(mem, sol);
  
  free(path);
  free(sol);
  free(l);
}

void initiateStack(List *l, Memory *mem)
{
  for( int i=0; i<memSize; i++ )
    pushObject(l, newObject(mem, i, NULL));
}
