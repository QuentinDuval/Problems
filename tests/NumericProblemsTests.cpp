#include "NumericProblemsTests.h"
#include "NumericProblems.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void NumericProblemsTests::allTests()
   {
      kitayutaMartTests();
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
}
