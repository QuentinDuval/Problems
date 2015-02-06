#include "BinomialCoeff.h"
#include "DoubleLetter.h"
#include "EditDistance.h"
#include "Fibonacci.h"
#include "LongestIncreasingSeq.h"
#include "MakingChange.h"
#include "MaxContiguous.h"
#include "Sudoku.h"
#include "TaroProblems.h"
#include <iostream>

using namespace prob;


int main()
{
   binomialCoeffTests();
   doubleLetterTests();
   editDistanceTests();
   fiboTests();
   makingChangeTests();
   maxContiguousTest();
   longestIncreasingSeqTest();

   taroCoinsTests();
   taroGridTests();
   taroCuttingTests();

   sudokuTest();

   system("PAUSE");
}
