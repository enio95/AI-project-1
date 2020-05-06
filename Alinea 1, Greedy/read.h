#ifndef READINPUT
#define READINPUT

#include "errorMessage.h"
#include "point.h"

// change this value if max capacity is reached
#define MAXSIZE 10240

/* *p -> Endereço de um ponto
   nR -> Numero de rectangulos adjacentes ao ponto, p
   idR -> Array com os identificadores dos rectangulos adjacentes*/
typedef struct PointMemory
{
  Point *p;

  int nR; 

  int idR[3];
  
}PointMemory;

/* idR -> Identificador do rectangulo
   idP -> Array de pontos que veem idR
   np -> Numero de pontos que veem idR*/
typedef struct RecMemory
{
  int idR;

  Point *idP;

  int nP;
  
}RecMemory;

/* pMemSize -> numero de possições validas no array pMem
   pMemMaxSize -> numero maximo de posições valid no array pMem
   rMemMaxSize -> numero de posições validas no array rMem*/
typedef struct
{
  struct PointMemory *pMem;
  int pMemSize, pMemMaxSize;
  
  struct RecMemory *rMem;  
  int rMemMaxSize;
  
}Memory;

//API

/* Alloca memoria dinamicamente para a estrutura Memory e para os 
   seus arrays, PointMemory e RecMemory, retornado o seu apontador.*/
Memory *newMemory(int rMemSize);

/* Le todo o input e guarda a informação no argumento Memory *mem*/
void readInput(Memory *mem, int nR);

/* Le uma linha do input*/ 
void readLine(Memory *mem, RecMemory *rMem);

/* Se o ponto (*p) não esta contido no array PointMemory, 
   então adicionamos um ponto a memoria e o seu rectangulo 
   adjacente, caso contrario, adiciona-se o identificador 
   do rectangulo a posição que contem o ponto.*/
void addToPointMemory(Memory *mem, int index, Point *p, int idR);

/* Procura em PointMemory o ponto p. Retorna o indice
   do ponto caso esta contido, caso contrario retorna
   primeira possição não ocupada no array.*/
int searchPointMemory(PointMemory *pMem, Point *p, int iLim);

/* Faz print dos pontos e dos rectangulos*/
void printMemory(Memory *mem);

/* Para todos os pontos em PointMemory, iremos
   imprimir todos o rectanglos adjacentes*/
void printPointMemory(PointMemory *pMem, int iLim);

/* Imprime um array de inteiros*/
void printArray(int arr[], int iLim);

/* Para cada rectangulo faz print dos pontos que o veem*/
void printRecMemory(RecMemory *rMem, int iLim);

/* Ordenas as possições de memoria do array PointMemoria, 
   usando uma função build in do C, qsort*/
void sortPointMemory(PointMemory *pMem, int iLim);

/* Compara duas posições do array Pointmemory. Função usada 
   em sortPointMemory.*/
int comparePointMemory(const void *a, const void *b);

/* Liberta a memoria alocada dinamicamente para Memory *mem */
void freeMemory(Memory *mem);

/* Liberta a memoria alocada dinamicamente para o array de pontos*/
void freePointMemory(PointMemory *pMem, int iLim);

/* Liberta a memoria alocada dinamicamente para o array de rectangulos*/
void freeRecMemory(RecMemory *rMem, int iLim);

#endif
