#include <stdio.h>
#include <stdlib.h>

#include "point.h"
#include "read.h"

void eclipseMode(Memory *mem);
  
int main()
{
  int nR;
  scanf("%d", &nR);
  
  Memory *mem = newMemory(nR); //cria Memory do tamanho do número de retângulos

  readInput(mem, nR); //lê o input

  eclipseMode(mem);
  
  return 0;
}

//cria o ficheiro onde ficará a informação da instância do problema
void eclipseMode(Memory *mem)
{
  FILE *f = fopen("data.ecl", "w+");
  
  int nR = mem->rMemMaxSize;

  fprintf(f, "\nnrec(%2d).\n\n", nR); //imprime no ficheiro o número de retângulos na forma do predicado nrec/1
  
  int x, y;
  
  for( int i=0; i<mem->pMemSize; i++ )
    {
      x = mem->pMem[i].p->x;
      y = mem->pMem[i].p->y;

      fprintf(f, "p(%2d, %1d, %1d).\n", x*nR+y, x, y);	//atribuí um identificador específico a cada vértice guardado no
														//no predicado p/3 e imprime no ficheiro
    }

  fputc('\n', f);
  
  for( int i=0; i<mem->rMemMaxSize; i++ )
    {
      fprintf(f, "rec(%2d, %2d, [", mem->rMem[i].idR, mem->rMem[i].nP);	//atribuí a um predicado rec/3, que representa os 
																		//retângulos, o identificador, número de vértices que contém
																		//e uma lista com os identificadores dos vértices

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

  fprintf(f, "guardar([");	//predicado guardar/1 guarda a lista de todos os identificadores de retângulos
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
