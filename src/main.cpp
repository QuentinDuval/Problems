#include "ClassicDPProblemsTests.h"
#include "ClassicNumericProblemsTests.h"
#include "EightQueens.h"
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
   
   EightQueens::tests();
   sudokuTest();

   system("PAUSE");
}
