#include "errorMessage.h"

//Imprime erro de alocação de memória
void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed on %s", str);
  exit(EXIT_FAILURE);
  
}

//Imprime erro de índice demasiado pequeno
void errorMessageIllegalSize(char *str)
{
  fprintf(stderr, "List size is Lower than 0, error on %s", str);
  exit(EXIT_FAILURE);
}

//Imprime erro de tipo
void errorMessageListSize(char *str)
{
  fprintf(stderr, "List size does not match its contents, error on %s", str);
  exit(EXIT_FAILURE);
}

//Imprime erro de tipo de índice errado
void errorMessageIndex(char *str)
{
  fprintf(stderr, "you are suposed to insert the INDEX of your object. Failed on %s\n", str);
  exit(EXIT_FAILURE);    
}

//Imprime erro de capacidade máxima
void errorMessageMaxCapacity(char *str)
{
  fprintf(stderr, "Max capacity reached in %s\n", str);
  exit(EXIT_FAILURE);
}
