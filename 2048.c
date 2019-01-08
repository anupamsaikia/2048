#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define SIZE 4

int matrix[SIZE][SIZE];
int pmatrix[SIZE][SIZE]; //to store previous state of the matrix
int score = 0;

// Function to copy matrix to pmatrix
void snapshot()
{
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      pmatrix[i][j] = matrix[i][j];
}

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

int isChanged()
{
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      if (pmatrix[i][j] != matrix[i][j])
      {
        return 1;
      }
  return 0;
}

int isFull()
{
  int i, j;
  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      if (matrix[i][j] == 0)
      {
        return 0;
      }
  return 1;
}

int isMergePossible()
{
  int i, j;
  for (i = 0; i < SIZE - 1; i++)
    for (j = 0; j < SIZE - 1; j++)
      if (matrix[i][j] == matrix[i + 1][j] || matrix[i][j] == matrix[i][j + 1])
      {
        return 1;
      }
  return 0;
}

// Function to take input from keyboard
int getInput()
{
  char ch = getch();
  int r;
  switch (ch)
  {
  case 'w':
    r = 1;
    break;
  case 's':
    r = 2;
    break;
  case 'a':
    r = 3;
    break;
  case 'd':
    r = 4;
    break;
  case 'q':
    r = 0;
    break;
  default:
    r = getInput();
  }
  return r;
}

// Function to fill the gaps according to the current move
void fillGap(int currentMove)
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
            matrix[k + 1][j] = 0;
            k--;
          }
        }
    break;

  case 2:
    for (i = SIZE - 2; i >= 0; i--)
      for (j = 0; j < SIZE; j++)
        if (matrix[i][j])
        {
          k = i + 1;
          while (k < SIZE && matrix[k][j] == 0)
          {
            matrix[k][j] = matrix[k - 1][j];
            matrix[k - 1][j] = 0;
            k++;
          }
        }
    break;

  case 3:
    for (i = 0; i < SIZE; i++)
      for (j = 1; j < SIZE; j++)
        if (matrix[i][j])
        {
          k = j - 1;
          while (k >= 0 && matrix[i][k] == 0)
          {
            matrix[i][k] = matrix[i][k + 1];
            matrix[i][k + 1] = 0;
            k--;
          }
        }
    break;

  case 4:
    for (i = 0; i < SIZE; i++)
      for (j = SIZE - 2; j >= 0; j--)
        if (matrix[i][j])
        {
          k = j + 1;
          while (k < SIZE && matrix[i][k] == 0)
          {
            matrix[i][k] = matrix[i][k - 1];
            matrix[i][k - 1] = 0;
            k++;
          }
        }
    break;
  }
}

// Function to merge two adjacent numbers which are equal and retutn points obtained
int merge(int currentMove)
{
  int i, j, k;
  int points = 0;
  switch (currentMove)
  {
  case 1:
    for (i = 1; i < SIZE; i++)
      for (j = 0; j < SIZE; j++)
        if (matrix[i][j] && matrix[i][j] == matrix[i - 1][j])
        {
          matrix[i - 1][j] += matrix[i][j];
          matrix[i][j] = 0;
          points += matrix[i - 1][j];
        }
    break;
  case 2:
    for (i = SIZE - 2; i >= 0; i--)
      for (j = 0; j < SIZE; j++)
        if (matrix[i][j] && matrix[i][j] == matrix[i + 1][j])
        {
          matrix[i + 1][j] += matrix[i][j];
          matrix[i][j] = 0;
          points += matrix[i + 1][j];
        }
    break;
  case 3:
    for (i = 0; i < SIZE; i++)
      for (j = 1; j < SIZE; j++)
        if (matrix[i][j] && matrix[i][j] == matrix[i][j - 1])
        {
          matrix[i][j - 1] += matrix[i][j];
          matrix[i][j] = 0;
          points += matrix[i][j - 1];
        }
    break;
  case 4:
    for (i = 0; i < SIZE; i++)
      for (j = SIZE - 2; j >= 0; j--)
        if (matrix[i][j] && matrix[i][j] == matrix[i][j + 1])
        {
          matrix[i][j + 1] += matrix[i][j];
          matrix[i][j] = 0;
          points += matrix[i][j + 1];
        }
    break;
  }
  fillGap(currentMove);
  return points;
}

// Function to add a number (2 or 4) at a random empty place
void addNewNum()
{
  int emptyPlaces[SIZE * SIZE][2], i, j, k = 0;

  for (i = 0; i < SIZE; i++)
    for (j = 0; j < SIZE; j++)
      if (!matrix[i][j])
      {
        emptyPlaces[k][0] = i;
        emptyPlaces[k][1] = j;
        k++;
      }

  int r = rand() % k;

  i = emptyPlaces[r][0];
  j = emptyPlaces[r][1];

  if (rand() % 10 < 1)
    matrix[i][j] = 4; // 10 % probability for 4
  else
    matrix[i][j] = 2; // 90 % probability for 2
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
  int i;
  do
  {
    i = getInput();

    if (i > 0 && i <= 4)
    {
      snapshot();
      fillGap(i);
      score += merge(i);

      if (!isFull() && isChanged())
        addNewNum();

      printMatrix();
      
      if (isFull() && !isMergePossible())
        break;
    }


  } while (i);

  return 0;
}
