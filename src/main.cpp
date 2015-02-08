#include "ClassicDPProblemsTests.h"
#include "MakingChange.h"
#include "MaxContiguous.h"
#include "StringProblemsTests.h"
#include "Sudoku.h"
#include "TaroProblemsTests.h"
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
   TaroProblemsTests::allTests();

   sudokuTest();

   system("PAUSE");
}
