#include "object.h"

Object *newObject(Memory *mem, int index, Object *pai)
{
  Object *obj = (Object *)calloc(1, sizeof(Object));

  if ( obj==NULL )
    errorMessageMem("newObject");
  
  obj->index = index;

  obj->pai = pai;
  
  obj->g = pai==NULL ? 0: pai->g + 1;
  
  obj->rec = (char *)calloc(nRec+1, sizeof(char));

  if ( obj->rec == NULL )
    errorMessageMem("newObject");

  obj->h = nRec;
  
  for( int i=0; i<3; i++ )
    if ( mem[index].rec[i] )
      {
	obj->rec[mem[index].rec[i]] = '1';
        obj->h--;
      }
  
  if ( pai!=NULL )
    for( int i=1; i<=nRec; i++ )
      if ( pai->rec[i]=='1' && obj->rec[i]!='1' )
	{
	  obj->rec[i] = '1';
	  obj->h--;
	}

  obj->h /= 3;
  
  return obj;	     
}

void freeObject(Object *obj)
{
  free(obj->rec);
  free(obj);
  obj = NULL;
}

void printObject(Object *obj)
{
  printf("%d\n", obj->index);

  printRec(obj->rec, nRec+1);

  putchar('\n');
}

void printRec(char *arr, int n)
{
  printf("{");

  for( int i=0; i<n; i++ )
    {
      printf("%d:%c", i, arr[i]=='1' ? '1': '0');

      if ( i!=n-1 )
	printf(", ");
    }

  printf("}\n");
}
