#include "point.h"


//inicializador do Ponto, recebe as duas coordenadas, aloca dinamicamente o espaço na memória para o Ponto e guarda os valores.
Point *newPoint(int x, int y)
{
  Point *p = (Point *)calloc(1, sizeof(Point));

  if ( p==NULL )
    errorMessageMem("newPoint");

  p->x = x;
  p->y = y;

  return p;  
}

//retorna se dois Point são iguais ou não
int equalPoint(Point *a, Point *b)
{
  return a->x==b->x && a->y==b->y ? 1: 0;
}

//compara dois Point
int comparePoint(Point *a, Point *b)
{
  return a->x==b->x  ? a->y-b->y: a->x-b->x;
}

//imprime as coordenadas do Point 
void printPoint(Point *p)
{
  printf("(%d, %d)\n", p->x, p->y);
}
