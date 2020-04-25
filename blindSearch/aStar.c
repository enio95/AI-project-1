#include "errorMessage.c"
#include "read.c"
#include "object.c"
#include "listObj.c"
#include "list.c"
#include "extraFunctions.c"
#include "heap.c"

void solve(Memory *mem);
void initiateHeap(ObjectArray *arr, Memory *mem, heap *h);


int main()
{
  int n;
  scanf("%d", &n);

  for ( int i=0; i<n; i++ )
    {
      printf("%d\n", i+1);
      Memory *mem = newMemory();
      readInput(mem);
      
      solve(mem);
      
      freeMemory(mem);
    }
  
  return 0;
}

void solve(Memory *mem)
{
  ObjectArray *arr = newObjectArray();
  
  heap *h = newHeap();
  initiateHeap(arr, mem, h);
  
  int heapIndex;
  Object *cur;
  
  while( !heapIsEmpty(h) )
    {
      heapIndex = extractFromHeap(h);
      cur = &arr->obj[heapIndex];
      
      // corrigir esta condição
      if ( reachedGoal(cur) && cur->g == nRec/3 + nRec%3 )
	break;

      else
	{
	  for( int i=cur->index+1; i<memSize; i++ )
	    {
	      addToObjectArray(arr, newObject(mem, i, cur));
	      insertInHeap(h, arr->size-1, arr->obj[i].g + arr->obj[i].h);
	    }
	}

      free(cur->rec);
      cur->rec = NULL;
    }
  
  printPath1(mem, cur);
  destroyHeap(h);
  freeObjectArray(arr);  
}

void initiateHeap(ObjectArray *arr, Memory *mem, heap *h)
{
  for( int i=0; i<memSize; i++ )
    {
      addToObjectArray(arr, newObject(mem, i, NULL));
      insertInHeap(h, i, arr->obj[i].g + arr->obj[i].h);
    }
}
