#pragma once

#include <string>
#include <utility>
#include <vector>


namespace prob
{
   /**
    * BuildingRoutes
    * http://community.topcoder.com/stat?c=problem_statement&pm=13193
    */
   struct BuildingRoutes
   {
      static int build(std::vector<std::string> const& distances, int safeThreshold);
   };

   /**
    * DoubleTree
    * http://community.topcoder.com/stat?c=problem_statement&pm=13359
    */
   struct DoubleTree
   {
      using Nodes = std::vector<int>;
      static int maximalScore(Nodes const& src1, Nodes const& dst1, Nodes const& src2, Nodes const& dst2, std::vector<int> const& values);
   };
}
