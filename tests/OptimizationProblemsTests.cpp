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
      januszTheBusinessmanTests();
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

   //--------------------------------------------------------------------------

   void OptimizationProblemsTests::januszTheBusinessmanTests()
   {
      assert(1 == JanuszTheBusinessman::minPromotions({ 0, 1, 4 }, { 5, 3, 10 }));

      assert(2 == JanuszTheBusinessman::minPromotions({ 2, 10, 6 }, { 6, 11, 9 }));
      assert(1 == JanuszTheBusinessman::minPromotions({ 2, 10, 23, 34, 45, 123, 1 }, { 25, 12, 40, 50, 48, 187, 365 }));
      assert(3 == JanuszTheBusinessman::minPromotions({ 8, 12, 20, 30, 54, 54, 68, 75 }, { 13, 31, 30, 53, 55, 70, 80, 76 }));
      
      assert(2 == JanuszTheBusinessman::minPromotions(
         { 124, 328, 135, 234, 347, 124, 39, 99, 116, 148 },
         { 237, 335, 146, 246, 353, 213, 197, 215, 334, 223 }));

      assert(14 == JanuszTheBusinessman::minPromotions(
         { 154, 1, 340, 111, 92, 237, 170, 113, 241, 91, 228, 134, 191, 86, 59, 115, 277, 328, 12, 6 },
         { 159, 4, 341, 118, 101, 244, 177, 123, 244, 96, 231, 136, 193, 95, 64, 118, 282, 330, 17, 13 }));
   }
}
