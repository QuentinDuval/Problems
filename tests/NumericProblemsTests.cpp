#include "NumericProblemsTests.h"
#include "NumericProblems.h"
#include "utils/Algorithms.h"
#include "utils/Numeric.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void NumericProblemsTests::allTests()
   {
      kitayutaMartTests();
      kingsFactorizationTests();
      waitingForBusTests();
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

   void NumericProblemsTests::waitingForBusTests()
   {
      auto areEqual = [](double a, double b) { return equalWithDelta(a, b, 1e-6); };
      assert(areEqual(9.5, WaitingForBus::whenWillBusArrive({ 5, 100 }, { 90, 10 }, 5)));
      assert(areEqual(4, WaitingForBus::whenWillBusArrive({ 5 }, { 100 }, 101)));
      assert(areEqual(3.666666666666667, WaitingForBus::whenWillBusArrive({ 5, 10 }, { 50, 50 }, 88888)));
      assert(areEqual(1.166666666666667, WaitingForBus::whenWillBusArrive({ 1, 2, 3, 4 }, { 10, 20, 30, 40 }, 1000)));
      assert(areEqual(21148.147303578935, WaitingForBus::whenWillBusArrive({ 10, 100, 1000, 10000, 100000 }, { 90, 4, 3, 2, 1 }, 100000)));
   }
}
