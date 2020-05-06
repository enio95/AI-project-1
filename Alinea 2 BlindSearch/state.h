#ifndef STATE
#define STATE

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "point.h"
#include "read.h"

/* idR -> Id of rectangles seen in the present state. Index is the
          identification of the rectangle 
	  idR[i]=0 means rec i has not been seen
          idR[i]>0 means rec i has been seen idR[i] times
   iLim -> size of idR. Usefull in some functions
   index -> Index of the last point seen
   pai -> Pointer to its father
   g -> path cost or size of path
   h -> under estimate of the cost to reach our goal
   f -> f=g+h its our under estimate of our path cost if we reach a sol
   seen -> Numeber of different rectangles present in the state*/
typedef struct State
{
  int *idR; 

  int iLim; 
  
  int index; 

  struct State *pai; 

  int g, h, f;

  int seen;
  
}State;


/* Aloca dinamicamente memoria para um novo estado e retorna o seu apontador.
   Esta função ira copiar toda a informação contida em pai e ira adicionar 
   um novo ponto que esta no indice index. 
   Caso o pai seja null, então iremos buscar apenas a informação contida no 
   ponto de indice index
   nRec -> Nº maximo de rectangulos*/
State *newState(PointMemory *pMem, int index, State *pai, int nRec);

/* Copia o conteudo de vec para arr, de 0 à iLim*/
void copyIntArray(int *arr, int *vec, int iLim);

/* Adiciona os rectangulos adjancentes do novo ponto (vec*)
   ao array idR do estado (arr)*/
void getNewRectangles(int *arr, int *vec, int iLim);

/* Calcula o numero de rectangulos que o estado state esta a ver*/
void calculateSeen(State *state, int iLim);

/* Liberta a memoria alocada dinamicamente em newState/4*/
void freeState(State *state);

/* Liberta o array idR*/
void freeStateIdR(State *state);

/* Faz print de todas as variaveis contidas em state*/
void printState(State *state);

/* Faz print de um array de 1 á iLim*/
void printIntArray(int *arr, int iLim);
  
#endif
