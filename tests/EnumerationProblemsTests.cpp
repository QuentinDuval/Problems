#include "EnumerationProblemsTests.h"
#include "EnumerationProblems.h"
#include "utils/Algorithms.h"
#include "utils/Numeric.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void EnumerationProblemsTests::allTests()
   {
      theNumberGameTests();
      fixedDiceGameDiv1Tests();
   }

   //--------------------------------------------------------------------------

   void EnumerationProblemsTests::theNumberGameTests()
   {
      assert(true == TheNumberGame::manaoWin(45, 4));
      assert(true == TheNumberGame::manaoWin(45, 5));
      assert(false == TheNumberGame::manaoWin(99, 123));
      assert(false == TheNumberGame::manaoWin(2356236, 5666));
   }

   //--------------------------------------------------------------------------

   void EnumerationProblemsTests::fixedDiceGameDiv1Tests()
   {
      auto test = [](double a, double b) { return equalWithDelta(a, b, 1e-3); };

      assert(2.0 == FixedDiceGameDiv1::getExpectation(1, 2, 1, 5));
      assert(3.0 == FixedDiceGameDiv1::getExpectation(3, 1, 1, 3));
      assert(test(3.4999999999999996, FixedDiceGameDiv1::getExpectation(1, 5, 1, 1)));
      assert(-1 == FixedDiceGameDiv1::getExpectation(2, 6, 50, 30));
      //assert(test(369.8865999182022, FixedDiceGameDiv1::getExpectation(50, 11, 50, 50))); //Because of overflow...
   }
}