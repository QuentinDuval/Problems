#include "OptimizationProblemsTests.h"
#include "OptimizationProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void OptimizationProblemsTests::allTests()
   {
      jumpFurtherTests();
      consecutiveIntegersDivOneTests();
   }

   //--------------------------------------------------------------------------

   void OptimizationProblemsTests::jumpFurtherTests()
   {
      assert(3 == JumpFurther::furthest(2, 2));
      assert(2 == JumpFurther::furthest(2, 1));
      assert(5 == JumpFurther::furthest(3, 3));
      assert(1 == JumpFurther::furthest(1, 757065));
      assert(862641 == JumpFurther::furthest(1313, 5858));
   }

   //--------------------------------------------------------------------------

   void OptimizationProblemsTests::consecutiveIntegersDivOneTests()
   {
      assert(2 == TheConsecutiveIntegersDivOne::find({ 4, 7, 47 }, 2));
      assert(0 == TheConsecutiveIntegersDivOne::find({ 1, 100 }, 1));
      assert(20 == TheConsecutiveIntegersDivOne::find({ -96, -53, 82, -24, 6, -75 }, 2));
      assert(24 == TheConsecutiveIntegersDivOne::find({ 64, -31, -56 }, 2));
      assert(90 == TheConsecutiveIntegersDivOne::find({ -96, -53, 82, -24, 6, -75 }, 4));
   }
}
