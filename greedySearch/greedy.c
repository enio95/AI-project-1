#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "heap.h"

/* Greedy approach does not guarantee an optimal solution
   but is by FAR the fastest method*/

void solve(Memory *mem);
void initiateHeap(PointMemory *mem, Heap *h, int iLim);
void copyArray(int *arr, int *vec, int iLim);
void update(PointMemory *pMem, Heap *h, int *rec, int iLim);
void updatePosition(PointMemory *pMem, int *arr);
int member(int v, int *arr, int iLim);

  
int main()
{
  int wrSize;
  scanf("%d", &wrSize);

  for( int i=0; i<wrSize; i++ )
    {
      int caseSize;
      scanf("%d", &caseSize);
      
      Memory *mem = newMemory(caseSize);
      readInput(mem, caseSize);

      solve(mem);
      
      freeMemory(mem);
    }
  
  return 0;
}

void solve(Memory *mem)
{
  Heap *h = newHeap();
  initiateHeap(mem->pMem, h, mem->pMemSize);

  int solSize = 0;
  
  while ( !heapIsEmpty(h) )
    {
      int index = extractFromHeap(h);

      if ( mem->pMem[index].nR==0 )
	break;

      solSize++;
      
      printPoint(mem->pMem[index].p);

      int arr[3];
      copyArray(arr, mem->pMem[index].idR, 3);
      
      update(mem->pMem, h, arr, mem->pMemSize);
    }
  

  printf("Solution Size = %d\nEND\n\n", solSize);
  destroyHeap(h);
}

void initiateHeap(PointMemory *mem, Heap *h, int iLim)
{
  for( int i=0; i<iLim; i++ )
    insertInHeap(h, i, mem[i].nR);
}

void copyArray(int *arr, int *vec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    arr[i] = vec[i];
}

void update(PointMemory *pMem, Heap *h, int *rec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      updatePosition(&pMem[i], rec);

      changeValue(h, i, pMem[i].nR);
    }
}

void updatePosition(PointMemory *pMem, int *arr)
{
  if ( pMem->nR==0 )
    return;

  for( int i=0; i<3; i++ )
    if ( pMem->idR[i]!=0 && member(pMem->idR[i], arr, 3) )
      {
	pMem->idR[i]=0;
	pMem->nR--;
      }
}

int member(int v, int *arr, int iLim)
{
  for( int i=0; i<iLim; i++ )
    if ( arr[i]==v )
      return 1;

  return 0;
}
