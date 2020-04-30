#include "point.h"

Point *newPoint(int x, int y)
{
  Point *p = (Point *)calloc(1, sizeof(Point));

  if ( p==NULL )
    errorMessageMem("newPoint");

  p->x = x;
  p->y = y;

  return p;  
}

int equalPoint(Point *a, Point *b)
{
  return a->x==b->x && a->y==b->y ? 1: 0;
}

int comparePoint(Point *a, Point *b)
{
  return a->x==b->x  ? a->y-b->y: a->x-b->x;
}

void printPoint(Point *p)
{
  printf("(%d, %d)\n", p->x, p->y);
}
