#include "NumericProblemsTests.h"
#include "NumericProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void NumericProblemsTests::allTests()
   {
      kitayutaMartTests();
      kingsFactorizationTests();
   }

   //--------------------------------------------------------------------------

   void NumericProblemsTests::kitayutaMartTests()
   {
      assert(4 == KitayutaMart::lastPrice(3, 1));
      assert(2 == KitayutaMart::lastPrice(3, 2));
      assert(4 == KitayutaMart::lastPrice(5, 3));

      //assert(570312504 == KitayutaMart::lastPrice(1000000000, 1));
      //assert(493827168 == KitayutaMart::lastPrice(987654321, 876543210));
   }

   //--------------------------------------------------------------------------
   
   static bool kingsFactorizationTest(std::vector<long> const& given, long n, std::vector<long> const& expected)
   {
      return equal(expected, TheKingsFactorization::getVector(n, given));
   }

   void NumericProblemsTests::kingsFactorizationTests()
   {
      assert(kingsFactorizationTest({ 2, 3 }, 12, { 2, 2, 3 }));
      assert(kingsFactorizationTest({ 7 }, 7, { 7 }));
      assert(kingsFactorizationTest({ 2, 3, 7 }, 1764, { 2, 2, 3, 3, 7, 7 }));
      assert(kingsFactorizationTest({ 7 }, 49, { 7, 7 }));
      assert(kingsFactorizationTest({ 2, 5 }, 210, { 2, 3, 5, 7 }));
      assert(kingsFactorizationTest({ 2, 2, 2, 5, 5 }, 100000, { 2, 2, 2, 2, 2, 5, 5, 5, 5, 5 }));
   }
}
