#include "GraphProblemsTests.h"
#include "GraphProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void GraphProblemsTests::allTests()
   {
      buildingRoutesTests();
      doubleTreeTests();
      familyTests();
      hexagonalBoardTests();
   }

   //--------------------------------------------------------------------------

   void GraphProblemsTests::buildingRoutesTests()
   {
      assert(6 == BuildingRoutes::build(
       { "011",
         "101",
         "110" }, 1));

      assert(12 == BuildingRoutes::build(
       { "033",
         "309",
         "390" }, 1));

      assert(5 == BuildingRoutes::build(
      { "0123",
        "1023",
        "1203",
        "1230" }, 2));

      assert(40 == BuildingRoutes::build(
      {  "05789654",
         "10347583",
         "65085479",
         "55602398",
         "76590934",
         "57939045",
         "12345608",
         "68647640" }, 3));
   }

   //--------------------------------------------------------------------------
   
   void GraphProblemsTests::doubleTreeTests()
   {
      assert(1024 == DoubleTree::maximalScore(
         { 0, 0, 1 },
         { 1, 3, 2 },
         { 0, 0, 3 },
         { 1, 3, 2 },
         { 1000, 24, 100, -200 }
      ));

      assert(1324 == DoubleTree::maximalScore(
         { 0, 0, 1 },
         { 1, 3, 2 },
         { 0, 0, 3 },
         { 1, 3, 2 },
         { 1000, 24, 100, 200 }
      ));

      assert(0 == DoubleTree::maximalScore(
         { 0, 0, 1 },
         { 1, 3, 2 },
         { 0, 0, 3 },
         { 1, 3, 2 },
         { -1000, -24, -100, -200 }
      ));

      assert(200 == DoubleTree::maximalScore(
         { 0, 0, 1 },
         { 1, 3, 2 },
         { 0, 0, 3 },
         { 1, 3, 2 },
         { -1000, 24, 100, 200 }
      ));

      assert(5 == DoubleTree::maximalScore(
         { 0, 0, 1, 1, 2, 2 },
         {1, 2, 3, 4, 5, 6},
         {0, 0, 1, 1, 2, 2},
         {1, 2, 3, 4, 5, 6},
         {-3, 2, 2, -1, 2, 2, -1}
      ));

      assert(5 == DoubleTree::maximalScore(
         { 0, 0, 1, 1, 2, 2 },
         {1, 2, 3, 4, 5, 6},
         {0, 0, 0, 0, 0, 0},
         {1, 2, 3, 4, 5, 6},
         {-3, 2, 2, -1, 2, 2, -1}
      ));
   }

   //--------------------------------------------------------------------------

   void GraphProblemsTests::familyTests()
   {
      assert(true == Family::isFamily({ -1, -1, 0 }, { -1, -1, 1 }));
      assert(true == Family::isFamily({ -1, -1, -1, -1, -1 }, { -1, -1, -1, -1, -1 }));
      assert(false == Family::isFamily({ -1, -1, 0, 0, 1 }, { -1, -1, 1, 2, 2 }));

      assert(true == Family::isFamily(
         { -1, -1, -1, -1, 1, -1, 0, 5, 6, -1, 0, 3, 8, 6 },
         { -1, -1, -1, -1, 3, -1, 4, 6, 5, -1, 5, 4, 6, 1 }));

      assert(false == Family::isFamily(
         { -1, -1, -1, 2, 2, -1, 5, 6, 4, 6, 2, 1, 8, 0, 2, 4, 6, 9, -1, 16, -1, 11 },
         { -1, -1, -1, 1, 0, -1, 1, 4, 2, 0, 4, 8, 2, 3, 0, 5, 14, 14, -1, 7, -1, 13 }));
   }

   //--------------------------------------------------------------------------

   void GraphProblemsTests::hexagonalBoardTests()
   {
      assert(0 == HexagonalBoard::minColors(
      { "---",
        "---",
        "---" }));

      assert(1 == HexagonalBoard::minColors(
      {"-X--",
       "---X",
       "----",
       "-X--"}));

      assert(2 == HexagonalBoard::minColors(
       { "XXXX",
         "---X",
         "---X",
         "---X"}
      ));

      assert(3 == HexagonalBoard::minColors(
      { "XX-XX--"
      , "-XX-XXX"
      , "X-XX--X"
      , "X--X-X-"
      , "XX-X-XX"
      , "-X-XX-X"
      , "-XX-XX-" }));
   }
}
