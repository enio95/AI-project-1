#include "object.h"

Object *newObject(Memory *mem, Object *pai)
{
  Object *obj = (Object *)calloc(1, sizeof(Object));

  if ( obj==NULL )
    errorMessageMem("newObject");
  
  obj->mem = mem;

  obj->pai = pai;

  obj->g = pai==NULL ? 0: pai->g + 1;
  
  obj->rec = (int *)calloc(nRec+1, sizeof(int));

  if ( obj->rec == NULL )
    errorMessageMem("newObject");

  obj->h = nRec;
  
  for( int i=0; i<3; i++ )
    if ( mem->rec[i] )
      {
	obj->rec[mem->rec[i]] = 1;
        obj->h--;
      }
  
  if ( pai!=NULL )
    for( int i=0; i<=nRec; i++ )
      if ( pai->rec[i] )
	{
	  obj->rec[i] = 1;
	  obj->h--;
	}

  obj->h /= 3;
  
  return obj;	     
}

void printObject(Object *obj)
{
  printPoint(obj->mem->p);

  printRec(obj->rec, nRec+1);

  putchar('\n');
}

void printRec(int *arr, int n)
{
  printf("{");

  for( int i=0; i<n; i++ )
    {
      printf("%d:%d", i, arr[i]);

      if ( i!=n-1 )
	printf(", ");
    }

  printf("}\n");
}

void printPath(Object *cur)
{
  if ( cur==NULL )
    return;

  printPoint(cur->mem->p);

  printPath(cur->pai);
}
