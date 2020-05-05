#ifndef READINPUT
#define READINPUT

#include "errorMessage.h"
#include "point.h"

// change this value if max capacity is reached
#define MAXSIZE 10240

//define PointMemory, estructura constituída por um Ponto, o número de retângulos adjacentes e o identificador desses retângulos
typedef struct PointMemory
{
  Point *p;

  int nR; 

  int idR[3]; //só pode ter no máximo três retângulos adjacentes, daí o tamanho máximo ser 3
  
}PointMemory;

//define RecMemory, estructura constítuida por um identificador de retângulos, array de Pontos que lhe pertencem e **nP**
typedef struct RecMemory
{
  int idR;

  Point *idP;

  int nP;
  
}RecMemory;

//define Memory, estructura constítuida por os Pontos e Retângulos
typedef struct
{
  struct PointMemory *pMem;
  int pMemSize, pMemMaxSize;
  
  struct RecMemory *rMem;  
  int rMemMaxSize;
  
}Memory;

//API
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
