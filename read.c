#include "read.h"

#ifndef ERROR
#include "errorMessage.c"
#endif


int comparePoint(Point *a, Point *b)
{
  return a->x==b->x ? a->y - b->y: a->x - b->x;
}

void printPoint(Point *p)
{
  printf("(%d, %d)\n", p->x, p->y);
}

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

  mem = NULL;
}

void readInput(Memory *mem)
{
  int num;
  scanf("%d", &num);

  for( int i=0; i<num; i++ )
    readLine(mem);
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

  mem->p.x = p->x; mem->p.y = p->y;

  mem->rec[mem->nr] = id;
  
  mem->nr++;
}

int voidPos(Memory *mem)
{
  Point p; p.x=0; p.y=0;
  
  return comparePoint(&mem->p, &p)==0 && mem->nr==0 ? 1: 0;
}

int searchMemory(Memory *mem, Point *p)
{  
  for( int i=0; i<memSize && i<MAXSIZE; i++ )
    if ( comparePoint(&mem[i].p, p)==0 )
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
  printPoint(&mem->p);

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
