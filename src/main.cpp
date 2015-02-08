#include "ClassicDPProblemsTests.h"
#include "StringProblemsTests.h"
#include "Sudoku.h"
#include "TaroProblemsTests.h"

#include <iostream>


int main()
{
   using namespace prob;

   ClassicDPProblemsTests::allTests();
   StringProblemsTests::allTests();
   TaroProblemsTests::allTests();
   sudokuTest();

   system("PAUSE");
}
