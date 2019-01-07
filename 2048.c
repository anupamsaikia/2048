#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define SIZE 4

int matrix[SIZE][SIZE];

void initMatrix()
{
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      matrix[i][j] = 0;

  i = rand() % 4;
  j = rand() % 4;
  matrix[i][j] = 2;

  i = rand() % 4;
  j = rand() % 4;
  matrix[i][j] = 2;
}

// Function to take input from keyboard
int input()
{
  char ch = getch();
  switch (ch)
  {
  case 'w':
    return 1;
    break;
  case 's':
    return 2;
    break;
  case 'a':
    return 3;
    break;
  case 'd':
    return 4;
    break;
  default:
    return 1;
  }
}

// Function to print the matrix
void printMatrix()
{
  int i, j;

  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
    {
      if (matrix[i][j] == 0)
        printf(".");
      else
        printf("%d", matrix[i][j]);
      printf("\t");
    }
    printf("\n");
  }

  printf("\n");
}

int main()
{
  srand(time(NULL));
  initMatrix();
  printMatrix();
  return 0;
}
