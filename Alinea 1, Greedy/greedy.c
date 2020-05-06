#include <stdio.h>
#include <stdlib.h>

#include "read.h"
#include "heap.h"

/* Greedy approach does not guarantee an optimal solution
   but is by FAR the fastest method*/

void solve(Memory *mem);
void initiateHeap(PointMemory *mem, Heap *h, int iLim);
void copyArray(int *arr, int *vec, int iLim);
void update(PointMemory *pMem, Heap *h, int *rec, int iLim);
void updatePosition(PointMemory *pMem, int *arr);
int member(int v, int *arr, int iLim);


/* wrSize --> numero de casos a analisar
   caseSize --> numero de rectangulos num dado caso*/
int main()
{
  int wrSize; 
  scanf("%d", &wrSize);

  for( int i=0; i<wrSize; i++ )
    {
      int caseSize; 
      scanf("%d", &caseSize);
      
      Memory *mem = newMemory(caseSize); 
      readInput(mem, caseSize); 

      solve(mem); 
      
      freeMemory(mem); 
    }
  
  return 0;
}

/* Esta função encontra uma solução atraves do metodo greedy.
   Consiste em: 
   1) Inicializar uma heap, em que os indices dos pontos guardados
      em PointMemory representa os vertices da heap e as chaves o 
      numero de rectangulos adjacentes do dado ponto.
   2) Retirar da heap o ponto com mais rectangulos adjacentes
      i.e maior chave
   3) Fazer update, que consiste em remover todos os rectangulos
      visto pelo ponto dos outros pontos da heap
   4) Verificar se temos uma solução i.e se todos os rectangulos estão
      vigiados, caso se verifique saimos da função, caso contrario 
      voltamos ao ponto 2).*/
void solve(Memory *mem)
{
  Heap *h = newHeap();
  initiateHeap(mem->pMem, h, mem->pMemSize); 

  int solSize = 0; 
  
  while ( !heapIsEmpty(h) )
    {
      // extrai o ponto com mais rectangulos vigiados
      int index = extractFromHeap(h); 

      /* Significa que encontramos uma solução pois 
	 o resto dos pontos da heap não vêm mais
	 rectangulos*/
      if ( mem->pMem[index].nR==0 )
	break;

      solSize++;  
      
      printPoint(mem->pMem[index].p); 

      /* As seguintes linhas fazem update dos pontos que ja vimos*/
      int arr[3];
      copyArray(arr, mem->pMem[index].idR, 3);       
      update(mem->pMem, h, arr, mem->pMemSize); 
    }
  

  printf("Solution Size = %d\nEND\n\n", solSize); 
  destroyHeap(h); 
}

/* Esta função põe os indices de todos os pontos contidos
   em PointMemory na Heap*/
void initiateHeap(PointMemory *mem, Heap *h, int iLim)
{
  for( int i=0; i<iLim; i++ )
    insertInHeap(h, i, mem[i].nR);
}

/* Copia o conteudo do array vec[] para o array arr[]*/
void copyArray(int *arr, int *vec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    arr[i] = vec[i];
}

/* Esta é a função mais importante de todo o programa
   Basicamente ela remove em todas as possições de 
   PointeMemory os rectangulos que ja vimos e tambem 
   atualiza a heap*/
void update(PointMemory *pMem, Heap *h, int *rec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      updatePosition(&pMem[i], rec); 

      changeValue(h, i, pMem[i].nR);
    }
}

/* Nesta função, iremos remover de uma  posição 
   de memoria aka ponto, os rectangulos que ja vimos.*/
void updatePosition(PointMemory *pMem, int *arr)
{
  /*retorna se o ponto não tiver retângulos adjacentes*/
  if ( pMem->nR==0 ) 
    return;

  /* Basicamente se o ponto conter um identificador do 
     rectangulo adjacente que estaja contido em arr[],
     em que arr[] é o conjunto de rectangulos que ja vimos, 
     então removemos este rectangulo deste ponto*/
  for( int i=0; i<3; i++ ) 
    if ( pMem->idR[i]!=0 && member(pMem->idR[i], arr, 3) )
      {
	pMem->idR[i]=0;
	pMem->nR--;
      }
}

/* Retorna 1 caso v pertença a arr[],
   caso contrario 0.*/
int member(int v, int *arr, int iLim)
{
  for( int i=0; i<iLim; i++ )
    if ( arr[i]==v )
      return 1;

  return 0;
}
