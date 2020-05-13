#include "extraFunctions.h"

int isSolution(State *state)
{
  for( int i=1; i<=state->iLim; i++ )
    if ( state->idR[i]==0 )
      return 0;

  return 1;
}

void updatePath(IList *path, int index)
{
  while ( path->size>0 && topInteger(path) > index )
    popInteger(path);

  pushInteger(path, index);  
}

void bestPath(IList *sol, IList *path)
{
  if ( sol->size==0 || sol->size > path->size )
    {
      while ( sol->size>0 )
	dequeueInteger(sol);
      
      for( INode *cur = path->first->next; cur!=path->last; cur=cur->next )
	enqueueInteger(sol, cur->value);
    }
}

State *randomSolution(Memory *mem, char *seen)
{
  State *state = NULL;
  State *cur;

  int index;
  
  do
    {
      index = pickRandomPoint(mem->pMem, seen, mem->pMemSize);
      
      cur = newState(mem->pMem, index, state, mem->rMemMaxSize);

      if ( state!=NULL )
	freeState(state);

      state = cur;

    }while ( state->seen<mem->rMemMaxSize );

  return state;
}

int pickRandomPoint(PointMemory *pMem, char *seen, int iLim)
{
  int index = rand()%iLim;
  
  while ( seen[index]=='1' )
    moveIndexLeft(&index, iLim);

  seen[index] = '1';
  
  return index;
}

void moveIndexLeft(int *index, int iLim)
{
  (*index)--;

  if ( (*index) < 0 )
    (*index)=iLim-1;
}

/*-------------------------------Print---------------------------*/
// print path while destroying
void printPath(PointMemory *pMem, IList *path)
{
  int temp = path->size;

  while ( path->size>0 )
    printPoint(pMem[popInteger(path)].p);

  printf("size = %d\nEND\n\n", temp);
}

// print path without destroying
void printPath1(PointMemory *pMem, IList *path)
{
  int temp = path->size;

  for( INode *cur = path->first->next; cur!=path->last; cur=cur->next )
    printPoint(pMem[cur->value].p);
  
  printf("size = %d\nEND\n\n", temp);
}

// print path from son to father untill we reach null
void printPath2(PointMemory *pMem, State *cur, int i)
{
  if ( cur==NULL )
    {
      printf("Size = %d\nEND\n\n", i);
      return;
    }
       
  printPoint(pMem[cur->index].p);

  printPath2(pMem, cur->pai, i+1);
}

void printSolution(PointMemory *pMem, char *seen, int iLim)
{
  int size = 0;

  for( int i=0; i<iLim; i++ )
    if ( seen[i]=='1' )
      {
	printPoint(pMem[i].p);
	size++;
      }

  printf("Solution size = %d\nEND\n\n", size);    
}

/* Aqui verificamos se ao tirar o ponto pMem[index] do estado state, 
   se ele continua feasible, i.e continua a ver todos os rectangulos */
int feasible(State *state, PointMemory *pMem, int index, char *seen)
{
  // signifca que o ponto não esta no estado state
  if ( seen[index]!='1' )
    return 0;

  for( int i=0; i<3; i++ )
    {
      int ind = pMem[index].idR[i];

      if ( ind!=0 && state->idR[ind] - 1 <= 0 )
	return 0;
    }

  return 1;
}

/* Nesta função tiramos o ponto pMem[index] do estado state e retornamos
   um novo estado sem esse ponto. Atenção esta função não verifica se o 
   ponto pertence ao estado, esse trabalho tem que ser feito antes com
   a função feasible*/
State *takePoint(State *state, PointMemory *pMem, int index)
{
  State *new = copyState(state);
  new->index = index;
  new->f--;
  new->g--;
  
  for( int i=0; i<3; i++ )
    {
      int ind = pMem[index].idR[i];

      if ( ind!=0 )
	{
	  new->idR[ind]--;
	  state->sum--;
	}
    }

  return new;  
}
