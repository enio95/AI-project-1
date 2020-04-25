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

  int index; // index from Memory *mem

  struct Object *pai;
  
  int g, h;
  
}Object;

typedef struct ObjectArray
{
  Object *obj;

  int size, maxSize;
  
}ObjectArray;


ObjectArray *newObjectArray();
void addToObjectArray(ObjectArray *arr, Object *obj);

Object *newObject(Memory *mem, int index, Object *pai);

void freeObjectArray(ObjectArray *arr);
void freeObject(Object *obj);

void printObject(Object *obj);
void printRec(char *arr, int n);

#endif
