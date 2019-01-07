#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define SIZE 4

int matrix[SIZE][SIZE];
int currentMove = 1; // 1=up, 2=down, 3=left, 4=right

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
void input()
{
  char ch = getch();
  switch (ch)
  {
  case 'w':
    currentMove = 1;
    break;
  case 's':
    currentMove = 2;
    break;
  case 'a':
    currentMove = 3;
    break;
  case 'd':
    currentMove = 4;
    break;
  default:
    currentMove = 1;
  }
}

void fillGap()
{
  int i, j, k;
  switch (currentMove)
  {
  case 1:
    for (i = 1; i < SIZE; i++)
      for (j = 0; j < SIZE; j++)
        if (matrix[i][j])
        {
          k = i - 1;
          while (k >= 0 && matrix[k][j] == 0)
          {
            matrix[k][j] = matrix[k + 1][j];
            matrix[k+1][j] = 0;
            k--;
          }
        }

  case 2:
    for (i = 0; i < SIZE - 1; i++)
      for (j = 0; j < SIZE; j++)
        if (matrix[i][j])
        {
          k = i + 1;
          while (k < SIZE && matrix[k][j] == 0)
          {
            matrix[k][j] = matrix[k - 1][j];
            matrix[k-1][j] = 0;
            k++;
          }
        }


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
