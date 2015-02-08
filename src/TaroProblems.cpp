#include "TaroProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>


namespace prob
{
   //--------------------------------------------------------------------------
   // TARO COINS dummy implementation (no dynamic programming)
   //--------------------------------------------------------------------------

   static long taroCoins(long long n, long long kPower)
   {
      if (n == 0)          return 1;
      if (n < 0)           return 0;
      if (kPower == 0)     return 0;
      if (4 * kPower < n)  return 0;

      long long nextPower = kPower / 2;
      size_t nb = taroCoins(n, nextPower);
      nb += taroCoins(n - kPower, nextPower);
      nb += taroCoins(n - 2 * kPower, nextPower);
      return nb;
   }

   long taroCoins(long long n)
   {
      long double maxK = std::floor(std::log2(n));
      long double kPower = std::pow(2, maxK);
      return taroCoins(n, static_cast<long>(kPower));
   }

   //--------------------------------------------------------------------------
   // TARO GRID
   //--------------------------------------------------------------------------

   size_t taroGrid(std::vector<std::string> const& lines, char searchedChar)
   {
      size_t maxCount = 0;
      for (size_t col = 0; col < lines.size(); ++col)
      {
         size_t count = 0;
         for (auto& line : lines)
         {
            if (line[col] == searchedChar)
            {
               ++count;
               maxCount = std::max(maxCount, count);
            }
            else
            {
               count = 0;
            }
         }
      }
      return maxCount;
   }

   size_t taroGrid(std::vector<std::string> const& lines)
   {
      return std::max(taroGrid(lines, 'W'), taroGrid(lines, 'B'));
   }

   //--------------------------------------------------------------------------
   // TARO CUTTING
   //--------------------------------------------------------------------------

   struct Cutting
   {
      using Tree = std::pair<size_t, size_t>;
      using Trees = std::vector<Tree>;

      static int minLength(
         std::vector<size_t> const& initialHeights,
         std::vector<size_t> const& treeGrowth,
         std::vector<size_t> devices, size_t T)
      {
         /** Sorting the trees by decreasing growth */
         Trees trees(initialHeights.size());
         zipWith(initialHeights, treeGrowth, begin(trees), MakePair());
         std::sort(begin(trees), end(trees), reverseComparison(comparingWith(GetSecond())));

         /** Sorting the devices by increasing size */
         sort(devices.begin(), devices.end());

         size_t treeCount = trees.size();
         Matrix<size_t> solutions(treeCount + 1, devices.size() + 1, 1e9);
         solutions.at(0, 0) = 0;

         for (size_t day = 0; day < T; day++)
         {
            for (size_t tree = 0; tree < treeCount; tree++)
            {
               for (size_t dev = 0; dev <= devices.size(); dev++)
               {
                  /**
                   * Adding a tree to the problem:
                   * - If we do not use an additional tool, the height of the tree will grow to
                   * its maximum size, which is its initial size + the growth over the days
                   */
                  solutions.at(tree + 1, dev) = std::min(
                     solutions.at(tree + 1, dev),
                     solutions.at(tree, dev) + trees[tree].first + T * trees[tree].second
                     );

                  /**
                   * - If we use an additional tool, then the height of the tree will grow to
                   * its cut size (the one of the device) + the growth over the remaining days
                   */
                  if (dev < devices.size())
                  {
                     solutions.at(tree + 1, dev + 1) = std::min(
                        solutions.at(tree + 1, dev + 1),
                        solutions.at(tree, dev) + devices[dev] + day * trees[tree].second
                        );
                  }
               }
            }

            /** The best solution without devices at next day is the best of the solution at previous day */
            for (size_t tree = 0; tree <= treeCount; tree++)
               for (size_t dev = 0; dev <= devices.size(); dev++)
                  solutions.at(tree, 0) = std::min(solutions.at(tree, 0), solutions.at(tree, dev));
         }

         return solutions.at(treeCount, 0);
      }
   };

   size_t TaroCutting::minLength(Ints const& trees, Ints const& growths, Ints const& devices, size_t nbDays)
   {
      return Cutting::minLength(trees, growths, devices, nbDays);
   }
}
