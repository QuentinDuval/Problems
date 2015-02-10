#include "ClassicDPProblemsTests.h"
#include "ClassicNumericProblemsTests.h"
#include "StringProblemsTests.h"
#include "Sudoku.h"
#include "TaroProblemsTests.h"

#include <iostream>


int main()
{
   using namespace prob;

   ClassicDPProblemsTests::allTests();
   ClassicNumericProblemsTests::allTests();
   StringProblemsTests::allTests();
   TaroProblemsTests::allTests();
   sudokuTest();

   system("PAUSE");
}
