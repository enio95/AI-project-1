#ifndef HEAP
#define HEAP

#include <stdio.h>
#include <stdlib.h>

#include "errorMessage.h"

/*----------------------------------------------------------------
  --------------------------Made by Énio--------------------------
  -----------------------Last change 28/3/20----------------------*/

typedef struct
{
  int key;

  int vert;
  
}Hnode;

typedef struct Heap
{
  int size, maxSize;
  
  Hnode *arr;

  int memSize, memMaxSize;

  int *mem;
  
} Heap;
  

/*----------------------------Compare----------------------------*/
int compareKey(Hnode *, Hnode *);

/*----------------------------newHeap----------------------------*/
Heap *newHeap();

/*-----------------------------Insert-----------------------------*/
void insertInHeap(Heap *, int, int);

/*-----------------------------change----------------------------*/
void changeValue(Heap *, int, int);

/*----------------------------extract----------------------------*/
int extractFromHeap(Heap *);

/*------------------------Memory management------------------------*/
void moreMemory(Heap *);

void destroyHeap(Heap *);

/*------------------------------Sort------------------------------*/
void sort(Heap *, int);
void sortDown(Heap *, int);
void sortUp(Heap *, int);
void swap(Heap *, int, int);
int heapIsEmpty(Heap *);

/*---------------------------print heap---------------------------*/
void printHeap(Heap *);
void printSize(Heap *);
void auxPrint(Heap *, int, int);

/*-------------------------Non related func-------------------------*/
int power(int b, int exp);


#endif
