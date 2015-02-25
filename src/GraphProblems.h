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

   /**
    * Family
    * http://community.topcoder.com/stat?c=problem_statement&pm=10541
    */
   struct Family
   {
      static bool isFamily(std::vector<int> const& parent1, std::vector<int> const& parent2);
   };

   /**
    * HexagonalBoard
    * http://community.topcoder.com/stat?c=problem_statement&pm=12784
    */
   struct HexagonalBoard
   {
      static int minColors(std::vector<std::string> const& board);
   };

   /**
    * Egalitarianism
    * http://community.topcoder.com/stat?c=problem_statement&pm=12613
    */
   struct Egalitarianism
   {
      static int maxDifference(std::vector<std::string> const& isFriend, int diff);
   };

   /**
    * DancingFoxes
    * http://community.topcoder.com/stat?c=problem_statement&pm=12548
    */
   struct DancingFoxes
   {
      static int minimalDays(std::vector<std::string> const& friendship);
   };
}
