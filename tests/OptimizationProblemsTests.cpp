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
      buildingTowersEasyTests();
      zooExchangeProgramTests();
      shoppingSurveyDiv1Tests();
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

   //--------------------------------------------------------------------------

   void OptimizationProblemsTests::buildingTowersEasyTests()
   {
      assert(3 == BuildingTowersEasy::maxHeight(10, { 3, 8 }, { 1, 1 }));
      assert(99999 == BuildingTowersEasy::maxHeight(100000, {}, {}));
      assert(2717 == BuildingTowersEasy::maxHeight(2718, { 1, 30, 400, 1300, 2500 }, { 100000, 100000, 100000, 100000, 100000 }));
      assert(8 == BuildingTowersEasy::maxHeight(20, { 4, 7, 13, 15, 18 }, { 3, 8, 1, 17, 16 }));

      assert(120 == BuildingTowersEasy::maxHeight(447,
         { 32, 35, 55, 60, 61, 88, 91, 97, 128, 151, 181, 186, 192, 196, 198, 237, 259, 268, 291, 314, 341, 367, 389, 390, 391, 428, 435 },
         { 81, 221, 172, 641, 25, 953, 330, 141, 123, 440, 692, 394, 200, 649, 78, 726, 50, 810, 501, 4, 216, 407, 2, 172, 0, 29, 14 }));

      assert(6343 == BuildingTowersEasy::maxHeight(97638,
         { 8, 1749, 4550, 5388, 6752, 7089, 9737, 14891, 16671, 16821, 17691, 19753, 24589,
         25348, 30114, 32213, 34376, 36467, 37699, 41490, 44784, 44893, 57316, 58275, 58567,
         61122, 61489, 63195, 64776, 65905, 68788, 69908, 72853, 78152, 78784, 82779, 84488,
         86277, 88611, 92793, 93214, 97583 },
         { 16610, 6, 497, 14, 42892, 31, 79, 1203, 518, 31147, 597, 7846, 1396, 8309, 12, 14, 1148,
         433, 23693, 13, 1939, 244, 19, 46, 27, 611, 412, 10, 27023, 19141, 34, 15667, 588, 10, 229,
         83, 390, 14, 38441, 16021, 4, 39386 }));
   }

   //--------------------------------------------------------------------------

   void OptimizationProblemsTests::zooExchangeProgramTests()
   {
      assert(1 == ZooExchangeProgram::minGroup({ 2, 1, 3 }, 1, 3));
      assert(2 == ZooExchangeProgram::minGroup({ 3, 4, 1, 3, 4, 2 }, 1, 3));
      assert(2 == ZooExchangeProgram::minGroup({ 3, 4, 3, 1, 6, 2, 5, 7, 5, 2 }, 2, 6));
      assert(-1 == ZooExchangeProgram::minGroup({ 3, 1, 4 }, 2, 4));
      assert(1 == ZooExchangeProgram::minGroup({ 2, 1, 3, 1, 4 }, 1, 4));
      assert(3 == ZooExchangeProgram::minGroup({ 7, 12, 2, 12, 10, 13, 6, 5, 3, 3, 4, 11, 12, 4, 3, 1, 8, 11, 4, 7, 6, 5, 47 }, 2, 7));
   }

   //--------------------------------------------------------------------------

   void OptimizationProblemsTests::shoppingSurveyDiv1Tests()
   {
      assert(0 == ShoppingSurveyDiv1::minValue(10, 2, { 1, 2, 3 }));
      assert(1 == ShoppingSurveyDiv1::minValue(5, 2, { 1, 2, 3 }));
      assert(2 == ShoppingSurveyDiv1::minValue(4, 4, { 4, 4, 4, 2 }));
      assert(10 == ShoppingSurveyDiv1::minValue(20, 3, { 1, 10, 3, 4, 8, 15, 3, 16, 18, 2, 7, 3 }));
      assert(2 == ShoppingSurveyDiv1::minValue(4, 2, { 1, 2, 1, 1, 3, 1, 2, 2, 1, 2, 1 }));
      assert(1 == ShoppingSurveyDiv1::minValue(2, 3, { 1, 1, 1, 2 }));
   }
}
