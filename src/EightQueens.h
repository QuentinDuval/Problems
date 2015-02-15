#pragma once

#include <utility>
#include <vector>


namespace prob
{
   struct EightQueens
   {
      using Position = std::pair<int, int>;
      using Positions = std::vector<Position>;

      static std::vector<Positions> allPositions();
      static void tests();
   };
}
