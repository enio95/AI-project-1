#ifndef OBJECT
#define OBJECT

#ifndef ERROR
#include "errorMessage.c"
#endif

#ifndef READINPUT
#include "read.c"
#endif

#ifndef POINT
#include "point.c"
#endif

typedef struct Object
{
  int *rec;

  Memory *mem;

  struct Object *pai;
  
}Object;

Object *newObject(Memory *mem, Object *pai);

void printObject(Object *obj);
void printRec(int *arr, int n);

void printPath(Object *obj);

#endif
