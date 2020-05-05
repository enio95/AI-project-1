#ifndef POINT
#define POINT

#include <stdio.h>
#include <stdlib.h>

#include "errorMessage.h"

//vértice, representado por um ponto com duas coordenadas
typedef struct Point
{
  int x, y;
  
}Point;

//API
Point *newPoint(int x, int y);
int equalPoint(Point *a, Point *b);
int comparePoint(Point *a, Point *b);
void printPoint(Point *p);

#endif
