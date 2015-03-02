#include "EnumerationProblemsTests.h"
#include "EnumerationProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void EnumerationProblemsTests::allTests()
   {
      theNumberGameTests();
   }

   //--------------------------------------------------------------------------

   void EnumerationProblemsTests::theNumberGameTests()
   {
      assert(true == TheNumberGame::manaoWin(45, 4));
      assert(true == TheNumberGame::manaoWin(45, 5));
      assert(false == TheNumberGame::manaoWin(99, 123));
      assert(false == TheNumberGame::manaoWin(2356236, 5666));
   }
}
