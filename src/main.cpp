#include "ClassicDPProblemsTests.h"
#include "ClassicNumericProblemsTests.h"
#include "NumericProblemsTests.h"
#include "OptimizationProblemsTests.h"
#include "StringProblemsTests.h"
#include "Sudoku.h"
#include "TaroProblemsTests.h"

#include <iostream>


int main()
{
   using namespace prob;

   ClassicDPProblemsTests::allTests();
   ClassicNumericProblemsTests::allTests();
   NumericProblemsTests::allTests();
   OptimizationProblemsTests::allTests();
   StringProblemsTests::allTests();
   TaroProblemsTests::allTests();
   sudokuTest();

   //TODO - Eight queens

   system("PAUSE");
}
