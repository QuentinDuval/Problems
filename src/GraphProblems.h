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
}
