#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "read.h"

void eclipseMode(Memory *mem);
  
int main()
{
  int nR;
  scanf("%d", &nR);
  
  Memory *mem = newMemory(nR);

  readInput(mem, nR);

  eclipseMode(mem);
  
  return 0;
}

void eclipseMode(Memory *mem)
{
  FILE *f = fopen("data.ecl", "w+");
  
  int nR = mem->rMemMaxSize;

  fprintf(f, "\nnrec(%2d).\n\n", nR);
  
  int x, y;
  
  for( int i=0; i<mem->pMemSize; i++ )
    {
      x = mem->pMem[i].p->x;
      y = mem->pMem[i].p->y;

      fprintf(f, "p(%2d, %1d, %1d).\n", x*nR+y, x, y);
    }

  fputc('\n', f);
  
  for( int i=0; i<mem->rMemMaxSize; i++ )
    {
      fprintf(f, "rec(%2d, %2d, [", mem->rMem[i].idR, mem->rMem[i].nP);

      for( int j=0; j<mem->rMem[i].nP; j++ )
	{
	  x = mem->rMem[i].idP[j].x;
	  y = mem->rMem[i].idP[j].y;
	  
	  fprintf(f, "%2d", x*nR+y);

	  if ( j!=mem->rMem[i].nP-1 )
	    fprintf(f, ", ");
	}
            
      fprintf(f, "]).\n");
    }

  fputc('\n', f);

  fprintf(f, "guardar([");
  for( int i=1; i<=mem->rMemMaxSize; i++ )
    {
      fprintf(f, "%d", i);

      if ( i<mem->rMemMaxSize )
	fprintf(f, ", ");
    }
  fprintf(f, "]).\n");

  fputc('\n', f);
  
  fclose(f);
}
