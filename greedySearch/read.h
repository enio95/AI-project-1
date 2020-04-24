#include <stdio.h>
#include <stdlib.h>

#define READINPUT

#define MAXSIZE 1024

typedef struct
{
  int x, y;
  
}Point;

typedef struct
{
  Point p;

  int nr; 

  int rec[3]; 
  
}Memory;

// global variables
int memSize = 0, nRec = 0;

int comparePoint(Point *, Point *);
void printPoint(Point *);

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
