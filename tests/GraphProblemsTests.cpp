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
}