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

  
int main()
{
  int wrSize; //número de instâncias
  scanf("%d", &wrSize);

  for( int i=0; i<wrSize; i++ )
    {
      int caseSize; //número de retângulos
      scanf("%d", &caseSize);
      
      Memory *mem = newMemory(caseSize); //cria instância de Memory
      readInput(mem, caseSize); //lê todo o input

      solve(mem); //resolve o algoritmo
      
      freeMemory(mem); //liberta o espaço na memória para a próxima instância 
    }
  
  return 0;
}

//resolve o problema
void solve(Memory *mem)
{
  Heap *h = newHeap(); //cria uma nova heap 
  initiateHeap(mem->pMem, h, mem->pMemSize); //inicializa a heap com o conteúdo dos pontos contidos no array PointMemory

  int solSize = 0; //tamanho da solução
  
  while ( !heapIsEmpty(h) )
    {
      int index = extractFromHeap(h); //extrai o índice do PointMemory com número de retângulos adjacentes maior

      if ( mem->pMem[index].nR==0 )	//termina o ciclo se chegar a um ponto que não tem retângulos adjacentes
	break;

      solSize++;  //incrementa o tamanho da solução
      
      printPoint(mem->pMem[index].p); //imprime as coordenadas de um dos pontos onde se colocará a guarda

      int arr[3];
      copyArray(arr, mem->pMem[index].idR, 3); //copia o array de identificadores do Ponto com índice index para arr
      
      update(mem->pMem, h, arr, mem->pMemSize); //atualiza a heap 
    }
  

  printf("Solution Size = %d\nEND\n\n", solSize); //imprime o tamanho da solução
  destroyHeap(h); //destrói a heap
}

//insere todos os pontos em PointMemory na heap
void initiateHeap(PointMemory *mem, Heap *h, int iLim)
{
  for( int i=0; i<iLim; i++ )
    insertInHeap(h, i, mem[i].nR);
}

//copia dois arrays 
void copyArray(int *arr, int *vec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    arr[i] = vec[i];
}

//atualiza as pontos e reorganiza a heap
void update(PointMemory *pMem, Heap *h, int *rec, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      updatePosition(&pMem[i], rec); //atualiza os valores dos Pontos no array PointMemory 

      changeValue(h, i, pMem[i].nR); //atualiza os valores na heap 
    }
}

//atualiza os valores do Ponto de modo a reorganizar-se a heap
void updatePosition(PointMemory *pMem, int *arr)
{
  if ( pMem->nR==0 ) //retorna se o ponto não tiver retângulos adjacentes
    return;

//atualiza o número de retângulos adjacente de um certo ponto de modo a que,
//se o tal ponto partilhar identificadores de retângulos no seu array com arr 
//esses identificadores são retirados e o número de retângulos decrementado
  for( int i=0; i<3; i++ ) 
    if ( pMem->idR[i]!=0 && member(pMem->idR[i], arr, 3) )
      {
	pMem->idR[i]=0;
	pMem->nR--;
      }
}

//retorna se um valor é pertencente a um array ou não
int member(int v, int *arr, int iLim)
{
  for( int i=0; i<iLim; i++ )
    if ( arr[i]==v )
      return 1;

  return 0;
}
