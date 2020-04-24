#ifndef POINT
#define POINT

#ifndef ERROR
#include "errorMessage.c"
#endif

typedef struct Point
{
  int x, y;
  
}Point;

Point *newPoint(int x, int y);
int comparePoint(Point *a, Point *b);
void printPoint(Point *p);

#endif
