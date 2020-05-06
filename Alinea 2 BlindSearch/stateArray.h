#ifndef STATEARRAY
#define STATEARRAY

#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "error.h"

/* state -> Array de tipo State
   size -> Tamanho currente do array state
   maxSize -> Tamanho maximo do array state*/
typedef struct StateArray
{
  State *state;

  int size, maxSize;
  
}StateArray;

/* Aloca memoria dinamicamente para um no StateArray e retorna o seu apontador*/
StateArray *newStateArray();

/* Adiciona o estado (state) ao array (arr)*/
void addToStateArray(StateArray *arr, State *state);

/* Liberta memoria alocada dinamicamente em newStateArray/0*/
void freeStateArray(StateArray *arr);

/* Faz print de todo o array chamando a função printState para cada posição*/
void printStateArray(StateArray *arr);

#endif
