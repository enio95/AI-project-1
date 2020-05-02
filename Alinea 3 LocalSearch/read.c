#include "read.h"

Memory *newMemory(int rMemSize)
{
  Memory *mem = (Memory *)calloc(1, sizeof(Memory));

  if ( mem==NULL )
    errorMessageMem("newMemory");

  mem->pMemSize = 0;
  mem->pMemMaxSize = MAXSIZE;

  mem->pMem = (PointMemory *)calloc(mem->pMemMaxSize, sizeof(PointMemory));

  if ( mem->pMem==NULL )
    errorMessageMem("newMemory");

  mem->rMemMaxSize = rMemSize;

  mem->rMem = (RecMemory *)calloc(mem->rMemMaxSize, sizeof(RecMemory));

  if ( mem->rMem==NULL )
    errorMessageMem("newMemory");

  return mem;
}

void readInput(Memory *mem, int nR)
{
  for( int i=0; i<nR; i++ )
    readLine(mem, &mem->rMem[i]);

  sortPointMemory(mem->pMem, mem->pMemSize);
}
 
void readLine(Memory *mem, RecMemory *rMem)
{
  int idR, nP;
  scanf("%d %d", &idR, &nP);

  rMem->idR = idR;
  
  rMem->nP = nP;
  rMem->idP = (Point *)calloc(nP, sizeof(Point));

  if ( rMem->idP==NULL )
    errorMessageMem("readLine");

  Point p;
  
  for( int i=0; i<nP; i++ )
    {
      scanf("%d %d", &p.x, &p.y);

      int index = searchPointMemory(mem->pMem, &p, mem->pMemSize);
      
      addToPointMemory(mem, index, &p, idR);
      
      rMem->idP[i].x = p.x;
      rMem->idP[i].y = p.y;
    }
}

void addToPointMemory(Memory *mem, int index, Point *p, int idR)
{
  if ( mem->pMem[index].p==NULL )
    mem->pMem[index].p = newPoint(p->x, p->y);
  
  mem->pMem[index].idR[mem->pMem[index].nR] = idR;

  mem->pMem[index].nR++;
  
  if ( mem->pMemSize==index )
    mem->pMemSize++;

  if ( mem->pMemSize==mem->pMemMaxSize )
    errorMessageMaxCapacity("addToPointMemory");
}

int searchPointMemory(PointMemory *pMem, Point *p, int iLim)
{
  for( int i=0; i<iLim && i<MAXSIZE; i++ )
    if ( equalPoint(pMem[i].p, p) )
	return i;

  return iLim;
}

void printMemory(Memory *mem)
{
  printPointMemory(mem->pMem, mem->pMemSize);
  printRecMemory(mem->rMem, mem->rMemMaxSize);
}

void printPointMemory(PointMemory *pMem, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      printPoint(pMem[i].p);
      printArray(pMem[i].idR, 3);
      putchar('\n');
      putchar('\n');
    }
}

void printArray(int arr[], int iLim)
{
  printf("[");
  for( int i=0; i<iLim; i++ )
    {
      printf("%d", arr[i]);

      if ( i!=iLim-1 )
	printf(", ");
    }

  printf("]");
}

void printRecMemory(RecMemory *rMem, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      printf("Rectangle: %d\n", rMem[i].idR);

      printf("Number of Points: %d\n", rMem[i].nP);

      for( int j=0; j<rMem[i].nP; j++ )
	printPoint(&rMem[i].idP[j]);

    }
}

void sortPointMemory(PointMemory *pMem, int iLim)
{
  qsort(pMem, iLim, sizeof(PointMemory), comparePointMemory);
}

int comparePointMemory(const void *a, const void *b)
{
  PointMemory *pMem1 = (PointMemory *)a;
  PointMemory *pMem2 = (PointMemory *)b;

  return comparePoint(pMem1->p, pMem2->p);
}

void freeMemory(Memory *mem)
{
  freePointMemory(mem->pMem, mem->pMemSize);
  
  freeRecMemory(mem->rMem, mem->rMemMaxSize);

  free(mem);
}

void freePointMemory(PointMemory *pMem, int iLim)
{
  for( int i=0; i<iLim; i++ )
    free(pMem[i].p);
  
  free(pMem);
}

void freeRecMemory(RecMemory *rMem, int iLim)
{
  free(rMem->idP);

  free(rMem);
}
