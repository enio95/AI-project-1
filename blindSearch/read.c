#include "read.h"

Memory *newMemory()
{
  Memory *mem = (Memory *)calloc(MAXSIZE, sizeof(Memory));

  if ( mem==NULL )
    errorMessageMem("newMemory");

  return mem;
}

void freeMemory(Memory *mem)
{
  if ( mem==NULL )
    errorMessageFree("freeMemory");

  free(mem);

  memSize = 0; nRec = 0;
  
  mem = NULL;
}

void readInput(Memory *mem)
{
  scanf("%d", &nRec);
  
  for( int i=0; i<nRec; i++ )
    readLine(mem);
  
  orderMemory(mem);
}

void readLine(Memory *mem)
{
  int id, nr;
  scanf("%d %d", &id, &nr);
  
  Point p;
  int index;
  
  for( int i=0; i<nr; i++ )
    {
      scanf("%d %d", &p.x, &p.y);

      index = searchMemory(mem, &p);

      addRec(&mem[index], &p, id);
    }
}

void addRec(Memory *mem, Point *p, int id)
{
  if ( memSize==MAXSIZE )
    errorMessageMaxCapacity("addRec");
  
  if ( voidPos(mem) )
    memSize++;

  mem->p = newPoint(p->x, p->y);
  
  mem->rec[mem->nr] = id;
  
  mem->nr++;
}

int voidPos(Memory *mem) { return mem->p==NULL ? 1: 0; }

int searchMemory(Memory *mem, Point *p)
{  
  for( int i=0; i<memSize && i<MAXSIZE; i++ )
    if ( comparePoint(mem[i].p, p)==0 )
      return i;

  return memSize;
}

void printMemory(Memory *mem)
{
  printf("MemorySize = %d\n\n", memSize);
  
  for( int i=0; i<memSize; i++ )
    printMember(&mem[i]);
}

void printMember(Memory *mem)
{
  printPoint(mem->p);

  printf("Numero de rectangulos adj = %d\n", mem->nr);

  printRecAdj(mem);
}

void printRecAdj(Memory *mem)
{
  printf("{");

  for( int i=0; i<3; i++ )
    {
      printf("%d", mem->rec[i]);

      if ( i+1<3 )
	printf(", ");

    }
  printf("}\n\n");
}

void orderMemory(Memory *mem)
{
  qsort(mem, memSize, sizeof(Memory), compareMemory);
}

int compareMemory(const void *a, const void *b)
{
  Memory *am = (Memory *)a;
  Memory *bm = (Memory *)b;
  
  return comparePoint(am->p, bm->p);
}
