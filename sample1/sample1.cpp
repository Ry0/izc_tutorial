#include <stdio.h>
#include "iz-c/iz.h"

#define NB_DIGITS 20
CSint **Digit;  // Digit is an array of 20 CSint variables
CSint *L1, *L2, *L3, *L4, *L5, *L6;

// Digit[a] = A, Digit[b] = B, ..., Digit[t] = T
enum {a = 0, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t};

void constraints()
{
  int val;

  Digit = cs_createCSintArray(NB_DIGITS, 0, 9);

  L1 = cs_VScalProd(3, Digit[a], Digit[b], Digit[c], 100, 10, 1);  // (d1)
  L2 = cs_VScalProd(3, Digit[d], Digit[e], Digit[f], 100, 10, 1);  // (d2)
  L3 = cs_VScalProd(3, Digit[g], Digit[h], Digit[i], 100, 10, 1);  // (d2)
  L4 = cs_VScalProd(3, Digit[j], Digit[k], Digit[l], 100, 10, 1);  // (d3)
  L5 = cs_VScalProd(3, Digit[m], Digit[n], Digit[o], 100, 10, 1);  // (d4)
  L6 = cs_VScalProd(5, Digit[p], Digit[q], Digit[r], Digit[s], Digit[t], // (d5)
                    10000, 1000, 100, 10, 1);

  cs_Eq(L6, cs_Mul(L1, L2));        // (a)
  cs_Eq(L3, cs_Mul(Digit[f], L1));  // (b)
  cs_Eq(L4, cs_Mul(Digit[e], L1));  // (c)
  cs_Eq(L5, cs_Mul(Digit[d], L1));  // (d)
  cs_Eq(L6, cs_VScalProd(3, L5, L4, L3, 100, 10, 1)); //(e)

  // (f)
  cs_NEQ(Digit[a], 0);
  cs_NEQ(Digit[d], 0);
  cs_NEQ(Digit[g], 0);
  cs_NEQ(Digit[j], 0);
  cs_NEQ(Digit[m], 0);
  cs_NEQ(Digit[p], 0);

  // (g)
  for (val = 0; val <= 9 ; val++) {
      cs_OccurConstraints(CSINT(2), val, Digit, NB_DIGITS);
  }
}

void printSolution(CSint **allvars, int nbVars)
{
  cs_printf("  %D\n", L1);
  cs_printf("* %D\n", L2);
  cs_printf("-----\n");
  cs_printf("  %D\n", L3);
  cs_printf(" %D \n", L4);
  cs_printf("%D  \n", L5);
  cs_printf("-----\n");
  cs_printf("%D  \n", L6);
  cs_printStats();
}

int main(int argc, char **argv)
{
  cs_init();

  constraints();
  cs_findAll(Digit, NB_DIGITS, cs_findFreeVarNbElements, printSolution);
  cs_printStats();

  cs_end();

  return 0;
}
