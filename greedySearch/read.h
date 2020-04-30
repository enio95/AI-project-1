#ifndef READINPUT
#define READINPUT

#include "errorMessage.h"
#include "point.h"

// change this value if max capacity is reached
#define MAXSIZE 10240

typedef struct PointMemory
{
  Point *p;

  int nR; 

  int idR[3]; 
  
}PointMemory;

typedef struct RecMemory
{
  int idR;

  Point *idP;

  int nP;
  
}RecMemory;

typedef struct
{
  struct PointMemory *pMem;
  int pMemSize, pMemMaxSize;
  
  struct RecMemory *rMem;  
  int rMemMaxSize;
  
}Memory;

Memory *newMemory(int rMemSize);

void readInput(Memory *mem, int nR);
void readLine(Memory *mem, RecMemory *rMem);
  
void addToPointMemory(Memory *mem, int index, Point *p, int idR);
int searchPointMemory(PointMemory *pMem, Point *p, int iLim);

void printMemory(Memory *mem);
void printPointMemory(PointMemory *pMem, int iLim);
void printArray(int arr[], int iLim);
void printRecMemory(RecMemory *rMem, int iLim);

void sortPointMemory(PointMemory *pMem, int iLim);
int comparePointMemory(const void *a, const void *b);

void freeMemory(Memory *mem);
void freePointMemory(PointMemory *pMem, int iLim);
void freeRecMemory(RecMemory *rMem, int iLim);

#endif
