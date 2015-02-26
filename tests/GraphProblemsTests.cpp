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
      egalitarianismTests();
      dancingFoxesTests();
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

   //--------------------------------------------------------------------------

   void GraphProblemsTests::egalitarianismTests()
   {
      assert(20 == Egalitarianism::maxDifference(
      { "NYN",
        "YNY",
        "NYN" }, 10));

      assert(-1 == Egalitarianism::maxDifference({ "NN", "NN" }, 10));
      assert(0  == Egalitarianism::maxDifference({ "NY", "YN" }, 0));

      assert(3000 == Egalitarianism::maxDifference
      ({ "NNYNNN",
         "NNYNNN",
         "YYNYNN",
         "NNYNYY",
         "NNNYNN",
         "NNNYNN" }, 1000));

      assert(-1 == Egalitarianism::maxDifference
      ({ "NNYN",
         "NNNY",
         "YNNN",
         "NYNN" }, 584));

      assert(20 == Egalitarianism::maxDifference
      ({ "NYNYYYN",
         "YNNYYYN",
         "NNNNYNN",
         "YYNNYYN",
         "YYYYNNN",
         "YYNYNNY",
         "NNNNNYN" }, 5));


      assert(2988 == Egalitarianism::maxDifference
      ({ "NYYNNNNYYYYNNNN",
         "YNNNYNNNNNNYYNN",
         "YNNYNYNNNNYNNNN",
         "NNYNNYNNNNNNNNN",
         "NYNNNNYNNYNNNNN",
         "NNYYNNYNNYNNNYN",
         "NNNNYYNNYNNNNNN",
         "YNNNNNNNNNYNNNN",
         "YNNNNNYNNNNNYNN",
         "YNNNYYNNNNNNNNY",
         "YNYNNNNYNNNNNNN",
         "NYNNNNNNNNNNNNY",
         "NYNNNNNNYNNNNYN",
         "NNNNNYNNNNNNYNN",
         "NNNNNNNNNYNYNNN" }, 747));
   }

   //--------------------------------------------------------------------------

   void GraphProblemsTests::dancingFoxesTests()
   {
      assert(1 == DancingFoxes::minimalDays
      ({ "NNY",
         "NNY",
         "YYN" }));

      assert(-1 == DancingFoxes::minimalDays
      ({ "NNNNN",
         "NNYYY",
         "NYNYY",
         "NYYNY",
         "NYYYN" }));

      assert(2 == DancingFoxes::minimalDays
      ({ "NNYYNN",
         "NNNNYY",
         "YNNNYN",
         "YNNNNY",
         "NYYNNN",
         "NYNYNN" }));

      assert(3 == DancingFoxes::minimalDays
      ({ "NNYNNNNYN",
         "NNNNYNYNN",
         "YNNYNYNNN",
         "NNYNYNYYN",
         "NYNYNNNNY",
         "NNYNNNYNN",
         "NYNYNYNNN",
         "YNNYNNNNY",
         "NNNNYNNYN" }));

      assert(0 == DancingFoxes::minimalDays({ "NY", "YN" }));

      assert(9 == DancingFoxes::minimalDays
      ({ "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNNNNN",
         "NNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNN",
         "NNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNY",
         "NNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNYYNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNYNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNYNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNYNNNN",
         "NNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNN",
         "NNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNYNNNNYNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNYNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNYNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNYNN",
         "NNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYN",
         "NNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNYNNNNYNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNYN",
         "NNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNN",
         "NNNNNNNNYNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNYNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNN",
         "NNYNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNY",
         "NNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNN",
         "NNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNYNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNYNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNNN",
         "NNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYYNNNNNNNNNNNNNNNNNN",
         "NNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNN",
         "NYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNN",
         "NNNNNNNYNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "YNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNYNNN",
         "NNNNNNNYNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNN",
         "NNNNNYNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNN",
         "NNNNNNNNNNNNNNNYNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNNNNNNNNNNNNNYNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
         "NNNNYNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNN" }));   
   }
}
