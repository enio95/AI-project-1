#include "read.h"

//cria uma instância Memory com tamanho igual ao número de retângulos na partição
Memory *newMemory(int rMemSize)
{
  Memory *mem = (Memory *)calloc(1, sizeof(Memory)); //instancia alocada dinamicamente

  if ( mem==NULL )
    errorMessageMem("newMemory");


  mem->pMemSize = 0; //número de pontos iniciais é 0
  mem->pMemMaxSize = MAXSIZE; // número de pontos máximos é MAXSIZE 

  mem->pMem = (PointMemory *)calloc(mem->pMemMaxSize, sizeof(PointMemory)); //inicializa o array de Pontos

  if ( mem->pMem==NULL )
    errorMessageMem("newMemory");

  mem->rMemMaxSize = rMemSize; //número máximo de retângulos é aqueles que estão na partição

  mem->rMem = (RecMemory *)calloc(mem->rMemMaxSize, sizeof(RecMemory)); //inicializa o array de retangulos

  if ( mem->rMem==NULL )
    errorMessageMem("newMemory");

  return mem;
}

//lê todos os retângulos e respetivos valores dos vértices e organiza o array dos Pontos
void readInput(Memory *mem, int nR)
{
  for( int i=0; i<nR; i++ )
    readLine(mem, &mem->rMem[i]);

  sortPointMemory(mem->pMem, mem->pMemSize);
}
 
//lê o retângulo pelo seu identificador, o número de vértices que o podem vigiar e os respetivos Pontos.
void readLine(Memory *mem, RecMemory *rMem)
{
  int idR, nP; //identificador do retângulo e número de vértices que o podem vigiar 
  scanf("%d %d", &idR, &nP);

  rMem->idR = idR;
  
  rMem->nP = nP;
  rMem->idP = (Point *)calloc(nP, sizeof(Point)); //inicializa o array de pontos.

  if ( rMem->idP==NULL )
    errorMessageMem("readLine");

  Point p;
  
  for( int i=0; i<nP; i++ )
    {
      scanf("%d %d", &p.x, &p.y);

      int index = searchPointMemory(mem->pMem, &p, mem->pMemSize); //procura se o ponto já existe para evitar pontos repetidos
      
      addToPointMemory(mem, index, &p, idR); //adiciona os pontos ao array PointMemory
      
      rMem->idP[i].x = p.x;
      rMem->idP[i].y = p.y;
    }
}

//adiciona um ponto à memória 
void addToPointMemory(Memory *mem, int index, Point *p, int idR)
{
  if ( mem->pMem[index].p==NULL ) //se não existir ponto, cria-se um novo com as coordenadas certas
    mem->pMem[index].p = newPoint(p->x, p->y);
  
  mem->pMem[index].idR[mem->pMem[index].nR] = idR; //o nR, número de retângulos, serve como o índice do possível seguinte retângulos	
												   //adiciona-se então o identificador de retângulos ao array no índice nR

  mem->pMem[index].nR++; //incrementa-se o número de retângulos adjacentes
  
  if ( mem->pMemSize==index ) //incrementa o número de pontos no caso de ser um novo ponto
    mem->pMemSize++;

  if ( mem->pMemSize==mem->pMemMaxSize ) //demasiados pontos
    errorMessageMaxCapacity("addToPointMemory");
}

//procura se um Point já existia previamente na memória. Se sim, retorna o iLim, número de pontos atual na memória, se não
//retorna o índice do ponto existente
int searchPointMemory(PointMemory *pMem, Point *p, int iLim)
{
  for( int i=0; i<iLim && i<MAXSIZE; i++ )
    if ( equalPoint(pMem[i].p, p) )
	return i;

  return iLim;
}

//imprime os conteúdos dos arrays de pontos e retângulos
void printMemory(Memory *mem)
{
  printPointMemory(mem->pMem, mem->pMemSize);
  printRecMemory(mem->rMem, mem->rMemMaxSize);
}

//imrpime todos os Point, e os respetivados retângulos ao quais são adjacentes
void printPointMemory(PointMemory *pMem, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      printPoint(pMem[i].p);
      printArray(pMem[i].idR, 3);
      putchar('\n');
      putchar('\n');
    }
}

//forma a impressão
void printArray(int arr[], int iLim)
{
  printf("[");
  for( int i=0; i<iLim; i++ )
    {
      printf("%d", arr[i]);

      if ( i!=iLim-1 )
	printf(", ");
    }

  printf("]");
}

//imprime o retângulo, o número de Pontos que têm e os conteúdos de cada ponto
void printRecMemory(RecMemory *rMem, int iLim)
{
  for( int i=0; i<iLim; i++ )
    {
      printf("Rectangle: %d\n", rMem[i].idR);

      printf("Number of Points: %d\n", rMem[i].nP);

      for( int j=0; j<rMem[i].nP; j++ )
	printPoint(&rMem[i].idP[j]);

    }
}

//ordena os pontos no array de pontos PointMemory de ordem crescente utilizando o algoritmo QuickSort
void sortPointMemory(PointMemory *pMem, int iLim)
{
  qsort(pMem, iLim, sizeof(PointMemory), comparePointMemory);
}

//retorna a comparação entre dois pontos
int comparePointMemory(const void *a, const void *b)
{
  PointMemory *pMem1 = (PointMemory *)a;
  PointMemory *pMem2 = (PointMemory *)b;

  return comparePoint(pMem1->p, pMem2->p);
}

/*------------------libertam o espaço ocupado por Memory em que freePointMemory liberta o espaço ocupado por Point Memory--------------------------*/
/*--------------------------------------------------------------freeRecMemory liberta o espaço ocupado por RecMemory-------------------------------*/
void freeMemory(Memory *mem)
{
  freePointMemory(mem->pMem, mem->pMemSize);
  
  freeRecMemory(mem->rMem, mem->rMemMaxSize);

  free(mem);
}

void freePointMemory(PointMemory *pMem, int iLim)
{
  for( int i=0; i<iLim; i++ )
    free(pMem[i].p);
  
  free(pMem);
}

void freeRecMemory(RecMemory *rMem, int iLim)
{
  free(rMem->idP);

  free(rMem);
}
