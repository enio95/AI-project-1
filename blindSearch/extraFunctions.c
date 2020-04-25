#include "extraFunctions.h"

int reachedGoal(Object *cur)
{
  for( int i=1; i<=nRec; i++ )
    if ( cur->rec[i]!='1' )
      return 0;

  return 1;
}

void updatePath(list *path, int index)
{
  while ( !isEmpty(path) && top(path) > index )
    pop(path);

  push(path, index);
}

void printPath(Memory *mem, list *path)
{
  printf("%d\n", path->size);
  
  while ( !isEmpty(path) )
    printPoint(mem[pop(path)].p);

  putchar('\n');
}

void printPath1(Memory *mem, Object *cur)
{
  if ( cur==NULL )
    {
      putchar('\n');
      return;
    }
  
  printPoint(mem[cur->index].p);

  printPath1(mem, cur->pai);  
}

void possibleSolution(list *sol, list *path)
{
  if ( sol->size==0 || sol->size >= path->size )
    {
      while( !isEmpty(sol) )
	dequeue(sol);

      for( lnode *cur = path->first->next; cur!=path->last; cur=cur->next )
	enqueue(sol, cur->value);
    }
}
