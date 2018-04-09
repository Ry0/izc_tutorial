#include <stdlib.h>
#include "iz-c/iz.h"

// This function is called when allvars[index] is instantiated
// It returns FALSE if Constraints Propagation fails
IZBOOL knownQueen(int val, int index, CSint **allvars, int NbQueens, void *extra)
{
  int i;

  for (i = 0; i < NbQueens; i++) {
    if (i != index) {
      CSint *var = allvars[i];

      if (cs_NEQ(var, val)==FALSE) return FALSE;  // 即値化されたvalと他のマス目allvars[i]が一致してはいけない
      if (cs_NEQ(var, val + index - i)==FALSE) return FALSE; // 対角線上に存在してはいけないvalから(index - i)分進んでvarと一致したらダメ
      if (cs_NEQ(var, val + i - index)==FALSE) return FALSE; // 一緒
    }
  }
  return TRUE;
}

int main(int argc, char **argv)
{
  int NbQueens = (argc > 1) ? atoi(argv[1]) : 8;
  CSint **allvars;

  cs_init();

  allvars = cs_createCSintArray(NbQueens, 1, NbQueens);

  cs_eventKnown(allvars, NbQueens, knownQueen, NULL);
  cs_search(allvars, NbQueens, cs_findFreeVarNbElementsMin);
  cs_printf("%A\n", allvars, NbQueens);

  cs_printStats();

  cs_end();

  return 0;
}