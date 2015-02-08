#include "BinomialCoeff.h"
#include "EditDistance.h"
#include "Fibonacci.h"
#include "LongestIncreasingSeq.h"
#include "MakingChange.h"
#include "MaxContiguous.h"
#include "StringProblemsTests.h"
#include "Sudoku.h"
#include "TaroProblems.h"
#include <iostream>

using namespace prob;


int main()
{
   binomialCoeffTests();
   editDistanceTests();
   fiboTests();
   makingChangeTests();
   maxContiguousTest();
   longestIncreasingSeqTest();

   StringProblemsTests::allTests();

   taroCoinsTests();
   taroGridTests();
   taroCuttingTests();

   sudokuTest();

   system("PAUSE");
}
