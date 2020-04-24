#ifndef READINPUT
#define READINPUT

#ifndef ERROR
#include "errorMessage.c"
#endif

#ifndef POINT
#include "point.c"
#endif

#define READINPUT

#define MAXSIZE 1024

typedef struct
{
  Point *p;

  int nr; 

  int rec[3]; 
  
}Memory;

// global variables
int memSize = 0, nRec = 0;

Memory *newMemory();
void freeMemory(Memory *);

void readInput(Memory *);
void readLine(Memory *);

void addRec(Memory *, Point *, int);
int voidPos(Memory *);

int searchMemory(Memory *, Point *);

void printMemory(Memory *);
void printMember(Memory *mem);
void printRecAdj(Memory *);

void orderMemory(Memory *mem);
int compareMemory(const void *a, const void *b);
  

#endif
