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
}
