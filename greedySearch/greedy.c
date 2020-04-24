#include "heap.c"
#include "read.c"

void solve(Memory *mem, heap *h);

void update(Memory *mem, heap *h, int *arr, int index);
void updateMember(Memory *mem, int *arr);

int contained(int v, int *arr);
void initiateArray(int *arr, int n, int v);

  
int main()
{
  int num;
  scanf("%d", &num);

  for( int i=0; i<num; i++ )
    {
      Memory *mem = newMemory();
      heap *h = newHeap();
      
      readInput(mem);
      
      for( int i=0; i<memSize; i++ )
	insertInHeap(h, i, mem[i].nr);
      
      solve(mem, h);

      memSize = 0;
      
      freeMemory(mem); destroyHeap(h);

      putchar('\n');
    }
  
  return 0;
}

void solve(Memory *mem, heap *h)
{
  int index;
  
  while ( !heapIsEmpty(h) )
    {
      index = extractFromHeap(h);

      if ( mem[index].nr==0 )
	break;

      printPoint(&mem[index].p);

      update(mem, h, mem[index].rec, index);

      mem[index].nr = 0;
      
      initiateArray(mem[index].rec, 3, 0);
    }
}

void update(Memory *mem, heap *h, int *arr, int index)
{
  for( int i=0; i<memSize; i++ )
    if ( i!=index )
      {
	updateMember(&mem[i], arr);

	changeValue(h, i, mem[i].nr);
      }
}

void updateMember(Memory *mem, int *arr)
{
  if ( mem->nr==0 )
    return;
  
  for( int i=0; i<3; i++ )
    if ( mem->rec[i]!=0 && contained(mem->rec[i], arr) )
      {
	mem->rec[i] = 0;
	mem->nr--;
      }
}

int contained(int v, int *arr)
{
  for( int i=0; i<3; i++ )
    if ( v == arr[i] )
      return 1;

  return 0;
}

void initiateArray(int *arr, int n, int v)
{
  for( int i=0; i<n; i++ )
    arr[i] = v;
}
