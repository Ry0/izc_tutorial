#include <stdlib.h>
#include <time.h>
#include "iz.h"

#define NB_CELLS 77
#define N -1

int Code[NB_CELLS] = {N,N,N,N,N,N,N,N,N,
                       N,N,2,2,2,2,N,N,
                      N,N,3,4,3,4,3,N,N,
                       N,3,3,3,3,3,3,N,
                      N,2,3,2,2,2,3,2,N,
                       N,2,2,2,2,2,2,N,
                      N,N,2,3,4,3,2,N,N,
                       N,N,2,3,3,2,N,N,
                      N,N,N,N,N,N,N,N,N};

void printCells(CSint **cell, int n, int nbCells)
{
  int i;

  for (i = 0; i < nbCells; i++) {
    if (Code[i + n] != N)
      printf("%d ", cs_getValue(cell[i + n]));
    else
      printf("  ");
  }
  printf("\n");
}

void printSolution(CSint **cell, int nbCells)
{
  int i;
  int n = 9;
  static int NbSolutions = 0;

  printf("\nSolution %d:\n", ++NbSolutions);
  for (i = 1; i < 8; i++)
    if (i % 2) {
      printf(" ");
      printCells(cell, n, 8);
      n += 8;
    }
    else {
      printCells(cell, n, 9);
      n += 9;
    }
}

CSint *getSum(int i, CSint **c)
{
  CSint **array = (CSint**) malloc(7 * sizeof(CSint*));
  int n = 0;

  // 隣り合う有効なセルが何個あるか（自分も含めて）
  array[n++] = c[i];
  if (Code[i + 1] != N) array[n++] = c[i + 1];
  if (Code[i + 9] != N) array[n++] = c[i + 9];
  if (Code[i + 8] != N) array[n++] = c[i + 8];
  if (Code[i - 1] != N) array[n++] = c[i - 1];
  if (Code[i - 9] != N) array[n++] = c[i - 9];
  if (Code[i - 8] != N) array[n++] = c[i - 8];
  CSint *sum = cs_Sigma(array, n);
  cs_printf("%T\n", sum);
  return sum;
}

int main(int argc, char **argv)
{
  int i;
  clock_t t0 = clock();
  CSint **cell;

  cs_init();

  cell = cs_createCSintArray(NB_CELLS, 0, 1);

  for (i = 0; i < NB_CELLS; i++)
    if (Code[i] == N)
      cs_EQ(cell[i], 0);
    else
      cs_EQ(getSum(i, cell), Code[i]);

  if (!cs_findAll(cell, NB_CELLS, cs_findFreeVar, printSolution))
    printf("No solution\n");

  cs_printStats();
  printf("Elapsed Time = %fs\n", (double) (clock() - t0) / CLOCKS_PER_SEC);

  cs_end();

  return 0;
}