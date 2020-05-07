#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void getAverage();
double readContent(FILE *f, int size);

void createFile();
void parentProcess(pid_t pid);
void childProcess();
  
void defineArgument(char **argv);
void createArgument(int n, int m);
char *newCharArray(int n);
void copyCharArray(char *str, char *vec);
  
char **argument;

int main(int argc, char **argv)
{  
  defineArgument(argv);

  createFile();

  getAverage();
}

void createFile()
{
  pid_t pid = fork();

  if ( pid < 0 )
    {
      fprintf(stderr, "Failed to fork\n");
      exit(EXIT_FAILURE);
    }

  if ( pid > 0 )
    parentProcess(pid);

  else
    childProcess();
}

void getAverage()
{
  FILE *f = fopen("times.txt", "r");

  if ( f==NULL )
    {
      fprintf(stderr, "Failed to open file\n");
      exit(EXIT_FAILURE);
    }

  int size;
  fscanf(f, "%d", &size);

  double sum = readContent(f, size);

  double avg = sum / size;

  printf("Average Time is %.2f\n", avg);
}

double readContent(FILE *f, int size)
{
  double sum = 0, temp;
  
  for( int i=0; i<size; i++ )
    {
      fscanf(f, "%lf", &temp);

      sum += temp;
    }

  return sum;
}

void parentProcess(pid_t pid)
{
  if ( waitpid(pid, NULL, 0) < 0 )
    {
      fprintf(stderr, "Failed to catch the exit\n");
      exit(EXIT_FAILURE);
    }
}

void childProcess()
{
  if ( execv(argument[0], argument) < 0 )
    {
      fprintf(stderr, "Error on execute\n");
      exit(EXIT_FAILURE);
    }
}

void defineArgument(char **argv)
{
  createArgument(8, 128);
  
  copyCharArray(argument[0], "getTimes.sh");
  copyCharArray(argument[1], argv[1]);
  copyCharArray(argument[2], argv[2]);
  copyCharArray(argument[3], argv[3]);
  copyCharArray(argument[4], "times.txt");

  argument[5] = NULL;  
}

void createArgument(int n, int m)
{
  argument = (char **)calloc(n, sizeof(char *));

  if ( argument==NULL )
    {
      fprintf(stderr, "Failed on memory alocation\n");
      exit(EXIT_FAILURE);
    }

  for( int i=0; i<n; i++ )
    argument[i] = newCharArray(m);
}

char *newCharArray(int n)
{
  char *temp = (char *)calloc(n, sizeof(char));

  if ( argument==NULL )
    {
      fprintf(stderr, "Failed on memory alocation\n");
      exit(EXIT_FAILURE);
    }

  return temp;  
}


void copyCharArray(char *str, char *vec)
{
  int i=0;
  
  do
    {
      str[i] = vec[i];

      i++;
      
    }while( vec[i]!='\0' );

  str[i] = '\0';
}
