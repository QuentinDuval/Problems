#include "EightQueens.h"

#include "utils/Algorithms.h"
#include "utils/Functors.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   template<int N>
   static bool containsBy(EightQueens::Positions& taken, size_t x)
   {
      for (auto& p : taken)
      {
         if (x == std::get<N>(p))
            return true;
      }
      return false;
   }

   static bool isDiagonalTaken(EightQueens::Positions& taken, EightQueens::Position const& pos)
   {
      for (auto& p : taken)
      {
         if (p.second - p.first == pos.second - pos.first) return true;
         if (p.second + p.first == pos.second + pos.first) return true;
      }
      return false;
   }

   static void eightQueens(std::vector<EightQueens::Positions>& solutions, EightQueens::Positions& taken)
   {
      if (8 == taken.size())
      {
         solutions.push_back(taken);
         return;
      }

      int x = 1 + taken.size();
      for (int y = 1; y <= 8; ++y)
      {
         if (containsBy<1>(taken, y) || isDiagonalTaken(taken, { x, y }))
            continue;

         taken.emplace_back(x, y);
         eightQueens(solutions, taken);
         taken.pop_back();
      }
   }

   std::vector<EightQueens::Positions> EightQueens::allPositions()
   {
      Positions taken;
      std::vector<Positions> solutions;
      eightQueens(solutions, taken);
      return solutions;
   }

   //--------------------------------------------------------------------------

   void EightQueens::tests()
   {
      auto solutions = EightQueens::allPositions();
      assert(92 == solutions.size());
   }
}
