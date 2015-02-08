#include "ClassicDPProblemsTests.h"
#include "StringProblemsTests.h"
#include "Sudoku.h"
#include "TaroProblemsTests.h"
#include <iostream>

using namespace prob;


int main()
{
   ClassicDPProblemsTests::allTests();
   StringProblemsTests::allTests();
   TaroProblemsTests::allTests();
   sudokuTest();

   system("PAUSE");
}
