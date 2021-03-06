#include "ClassicNumericProblemsTests.h"
#include "ClassicNumericProblems.h"

#include <assert.h>
#include <iostream>
#include <vector>


namespace prob
{
   void ClassicNumericProblemsTests::allTests()
   {
      gcdTests();
      closestPairsTests();
      lineIntersectionsTests();
      spellingNumberTests();
      randomShuffleTests();
      allSummingPairsTests();
   }

   //--------------------------------------------------------------------------

   void ClassicNumericProblemsTests::gcdTests()
   {
      assert(1 == gcd(17, 11));
      assert(2 == gcd(6, 8));
   }

   //--------------------------------------------------------------------------

   void ClassicNumericProblemsTests::closestPairsTests()
   {
      using Point = ClosestPairs::Point;

      std::vector<Point> points = { { 0, 0 }, { 2, 2 }, { 4, 2 }, { 5, 2 }, { 3, 4 } };
      auto res = ClosestPairs::find(points);
      assert(Point(4, 2) == res.first);
      assert(Point(5, 2) == res.second);
   }

   //--------------------------------------------------------------------------

   void ClassicNumericProblemsTests::lineIntersectionsTests()
   {
      std::vector<LineIntersection::HLine> hLines = {
         { 0, { 1, 10 } }, { 2, { 5, 7 } }
      };

      std::vector<LineIntersection::VLine> vLines = {
         { 8, { -5, 5 } }, { 6, { 1, 3 } }
      };

      auto res = LineIntersection::intersections(hLines, vLines);
      assert(2 == res.size());
      assert(LineIntersection::Point(6, 2) == res.at(0));
      assert(LineIntersection::Point(8, 0) == res.at(1));
   }

   //--------------------------------------------------------------------------

   void ClassicNumericProblemsTests::spellingNumberTests()
   {
      std::cout << 910313 << ": " << spellNumber(910313) << std::endl;
   }

   //--------------------------------------------------------------------------

   void ClassicNumericProblemsTests::randomShuffleTests()
   {
      std::vector<std::string> strings = { "a", "ab", "c", "ac", "b", "bc" };
      randomShuffle(strings);
   }

   //--------------------------------------------------------------------------
   
   void ClassicNumericProblemsTests::allSummingPairsTests()
   {
      std::vector<int> values{ 1, 1, -1, 2, 5, -3, -5, 11, -1 };
      auto pairs = AllSummingPairs::findPairs(values, 0);
      assert(5 == pairs.size());
   }
}
