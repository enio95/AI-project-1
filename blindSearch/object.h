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
  char *rec;

  Memory *mem;

  struct Object *pai;

  int g, h;
  
}Object;

typedef struct Path
{
  struct Path *prev;

  Point *p;
  
}Path;

Object *newObject(Memory *mem, Object *pai);

void printObject(Object *obj);
void printRec(char *arr, int n);

void printPath(Object *obj);

#endif
