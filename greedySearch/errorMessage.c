#include "errorMessage.h"

void errorMessageMem(char *str)
{
  fprintf(stderr, "Memory allocation failed on %s\n\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageFree(char *str)
{
  fprintf(stderr, "Failed to free memory in %s\n\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageMaxCapacity(char *str)
{
  fprintf(stderr, "Max capacity reached in %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageIllegalSize(char *str)
{
  fprintf(stderr, "List size is Lower than 0, error on %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageListSize(char *str)
{
  fprintf(stderr, "List size does not match its contents, error on %s\n", str);
  exit(EXIT_FAILURE);
}

void errorMessageIndex(char *str)
{
  fprintf(stderr, "you are suposed to insert the INDEX of your object. Failed on %s\n", str);
  exit(EXIT_FAILURE);    
}
