#include "TaroProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <algorithm>
#include <assert.h>
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

   void taroCoinsTests()
   {
      assert(1 == taroCoins(1));
      assert(3 == taroCoins(6));
      assert(2 == taroCoins(47));
      assert(9 == taroCoins(256));
      assert(6853 == taroCoins(8489289));
      assert(73411 == taroCoins(1000000000));
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

   void taroGridTests()
   {
      assert(1 == taroGrid({ "W" }));
      assert(1 == taroGrid({ "WB", "BW" }));
      assert(3 == taroGrid({ "BWW", "BBB", "BWB" }));
      assert(3 == taroGrid({ "BWB", "BBW", "BWB" }));

      assert(3 == taroGrid({
         "BWBW",
         "BBWB",
         "WWWB",
         "BWWW"}));

      assert(2 == taroGrid({
         "BBWWBBWW",
         "BBWWBBWW",
         "WWBBWWBB",
         "WWBBWWBB",
         "BBWWBBWW",
         "BBWWBBWW",
         "WWBBWWBB",
         "WWBBWWBB"}));
   }


   //--------------------------------------------------------------------------
   // TARO CUTTING
   //--------------------------------------------------------------------------

   struct Cutting
   {
      using Tree = std::pair<size_t, size_t>;
      using Trees = std::vector<Tree>;

      Cutting(TaroCutting::Ints const& trees, TaroCutting::Ints const& growths, TaroCutting::Ints const& devices)
         : m_trees(trees.size())
         , m_devices(devices)
      {
         std::sort(begin(m_devices), end(m_devices));
         zipWith(trees, growths, begin(m_trees), MakePair());
      }

      size_t minLength(size_t nbDays)
      {
         if (nbDays == 0)
         {
            size_t sum = 0;
            for (auto& t : m_trees) sum += t.first;
            return sum;
         }

         grow();
         std::sort(begin(m_trees), end(m_trees), reverseComparison(comparingWith(GetFirst())));

         Trees backUpTrees = m_trees;

         //Start using trees at t...
         size_t min = std::numeric_limits<size_t>::max();
         for (size_t t = 0; t < m_trees.size(); ++t)
         {
            bool didCut = false;
            for (size_t d = 0; d < m_devices.size(); ++d)
            {
               if (t + d >= m_trees.size()) break;
               if (m_devices[d] >= m_trees[t + d].first) break;

               m_trees[t + d].first = m_devices[d];
               didCut = true;
            }

            size_t res = minLength(nbDays - 1);
            min = std::min(min, res);
            m_trees = backUpTrees;

            if (!didCut)
               break;
         }

         return min;
      }

      void grow()
      {
         for (auto& t : m_trees)
            t.first += t.second;
      }

      Trees m_trees;
      TaroCutting::Ints m_devices;
   };

   //--------------------------------------------------------------------------

   struct TaroCutting2
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
      //Cutting cutting(trees, growths, devices);
      //return cutting.minLength(nbDays);

      return TaroCutting2::minLength(trees, growths, devices, nbDays);
   }

   //--------------------------------------------------------------------------

   void taroCuttingTests()
   {
      std::cout << std::endl << "Taro cutting:" << std::endl;
      std::cout << TaroCutting::minLength({ 4, 7 }, { 7, 1 }, { 7 }, 1) << std::endl;
      std::cout << TaroCutting::minLength({ 3, 1, 2 }, { 1, 1, 1 }, { 7, 7, 7 }, 2) << std::endl;
      std::cout << TaroCutting::minLength({ 100, 50 }, { 75, 30 }, { 200, 100, 50 }, 2) << std::endl;

      //Too long to compute for the dummy implementation
      std::cout << TaroCutting::minLength(
         { 7, 10, 1, 7, 5, 4, 11, 5, 7, 9, 10, 8 },
         { 1, 3, 4, 10, 2, 1, 6, 4, 8, 7, 5, 10 },
         { 7, 1, 5, 10 },
         3) << std::endl;

      std::cout << TaroCutting::minLength(
         { 35, 45, 32, 8 },
         { 2, 25, 31, 5 },
         { 29, 28, 3, 11, 28, 37 },
         8) << std::endl;

      //std::cout << TaroCutting::minLength({ 614, 649, 977, 808, 821, 356, 801, 493, 669, 650, 652, 627, 129, 261, 883, 513, 62, 698, 83, 772,
      //   779, 719, 83, 105, 774, 867, 412, 892, 142, 851, 743, 66, 221, 494, 125, 905, 638, 342, 723, 680,
      //   407, 197, 111, 368, 676, 694, 765, 482, 712, 188, 325, 535, 6, 49, 655, 595, 958, 805, 659, 893,
      //   370, 904, 276, 156, 29, 458, 757, 632, 731, 289, 582, 207, 843, 365, 387, 521, 69, 269, 459, 428,
      //   423, 885, 744, 199, 998, 968, 296, 473, 50, 752, 492, 919, 473, 981, 380, 896, 769, 991, 269, 93,
      //   108, 184, 762, 312, 511, 256, 374, 600, 643, 445, 908, 250, 384, 518, 119, 464, 499, 124, 82, 999,
      //   881, 767, 177, 796, 2, 620, 759, 380, 901, 221, 407, 622, 260, 622, 729, 264, 768, 79, 236, 524,
      //   437, 215, 108, 518, 820, 725, 490, 796, 986, 318 },
      //   { 391, 938, 772, 630, 54, 775, 379, 613, 647, 8, 946, 885, 604, 822, 663, 559, 452, 565, 637, 695, 24,
      //   515, 92, 956, 194, 551, 813, 362, 190, 268, 440, 781, 450, 789, 566, 372, 402, 860, 531, 608, 434,
      //   761, 754, 26, 504, 873, 132, 756, 206, 93, 284, 807, 642, 637, 936, 954, 205, 303, 582, 822, 134,
      //   269, 967, 147, 589, 549, 24, 670, 403, 105, 40, 531, 486, 695, 898, 287, 443, 542, 599, 151, 45,
      //   567, 548, 945, 912, 764, 451, 404, 700, 522, 227, 954, 84, 347, 625, 278, 377, 730, 635, 604, 959,
      //   845, 41, 193, 459, 532, 429, 216, 473, 415, 85, 933, 90, 643, 94, 927, 692, 99, 771, 594, 318, 627,
      //   89, 340, 110, 488, 909, 253, 20, 114, 179, 177, 116, 42, 676, 91, 787, 437, 551, 51, 880, 336, 759,
      //   795, 243, 727, 279, 620, 488, 607 },
      //   { 942, 79, 387, 184, 104, 981, 766, 678, 715, 998, 161, 125, 439, 532, 550, 415, 4, 467, 211, 852, 781,
      //   577, 728, 592, 40, 971, 852, 592, 338, 555, 662, 636, 823, 122, 728, 69, 701, 476, 346, 190, 36,
      //   535, 826, 739, 517, 551, 257, 36, 906, 171, 629, 292, 49, 29, 109, 151, 299, 180, 193, 731, 655,
      //   877, 174, 688, 866, 957, 57, 89, 513, 765, 68, 245, 454, 968, 224, 417, 657, 383, 769, 809, 13, 51,
      //   813, 970, 632, 357, 787, 717, 254, 645, 352, 636, 370, 950, 917, 959, 364, 453, 890, 43, 98, 438,
      //   748, 277, 115, 298, 431, 709, 312, 49, 553, 395, 798, 58, 419, 355, 770, 818, 460, 89, 880, 515,
      //   952, 219, 608, 284, 532, 254, 361, 524, 199, 265, 407, 782, 737, 928, 977, 729, 510, 175, 609, 81,
      //   155, 24, 425, 186, 999, 839, 896, 721 },
      //   150) << std::endl;
   }
}
