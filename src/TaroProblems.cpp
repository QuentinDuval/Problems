#include "TaroProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"

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
   // TARO CUTTING - Dummy implementation in factorial!
   //--------------------------------------------------------------------------

   struct DummyCutting
   {
      DummyCutting(TaroCutting::Ints const& trees, TaroCutting::Ints const& growths, TaroCutting::Ints const& devices)
         : m_trees(trees)
         , m_growths(growths)
         , m_devices(devices)
      {
         std::sort(begin(m_devices), end(m_devices));
      }

      size_t minLength(size_t nbDays)
      {
         std::vector<bool> marked(m_devices.size(), false);
         return minLength(m_trees.begin(), marked, m_devices.size(), nbDays);
      }

      size_t minLength(TaroCutting::Ints::iterator first, std::vector<bool>& marked, size_t deviceCount, size_t nbDays)
      {
         if (!deviceCount || first == m_trees.end())
         {
            std::vector<bool> marked(m_devices.size(), false);
            if (nbDays == 0)
               return sum(m_trees, 0);

            grow();
            size_t min = minLength(m_trees.begin(), marked, m_devices.size(), nbDays - 1);
            ungrow();
            return min;
         }

         size_t min = minLength(first + 1, marked, deviceCount, nbDays); //No devices used
         for (size_t d = 0; d < m_devices.size(); ++d)
         {
            if (marked[d] || m_devices[d] >= (*first))
               break;

            size_t backupHeight = *first;
            *first = m_devices[d];
            marked[d] = true;
            min = std::min(min, minLength(first + 1, marked, deviceCount - 1, nbDays));
            marked[d] = false;
            *first = backupHeight;
         }
         return min;
      }

      void grow()
      {
         for (size_t i = 0; i < m_trees.size(); ++i)
            m_trees[i] += m_growths[i];
      }

      void ungrow()
      {
         for (size_t i = 0; i < m_trees.size(); ++i)
            m_trees[i] -= m_growths[i];
      }

      TaroCutting::Ints m_trees;
      TaroCutting::Ints m_growths;
      TaroCutting::Ints m_devices;
   };

   /**
    * --------------------------------------------------------------------------
    * Cutting
    * --------------------------------------------------------------------------
    *
    * Key observations:
    * 
    * 1. The ordering of the tree is meaningless: the devices will make them even.
    * What really matters is which tools are used, what was the gain doing so.
    * But the growth of the tree should follow their tree.
    *
    * 2. At the last remaining day, the greedy approach is the best. For other days,
    * using the best devices for the highest tree is not necessarily optimal.
    *
    * 3. There is no reason to spare a device if it can be used on a tree.
    * But if a tall tree is left alone at one iteration, it can be cut later.
    */

   struct Cutting
   {
      Cutting(TaroCutting::Ints const& trees, TaroCutting::Ints const& growths, TaroCutting::Ints const& devices)
         : m_trees(trees)
         , m_growths(growths)
         , m_devices(devices)
      {
         std::sort(begin(m_devices), end(m_devices));
      }

      size_t minLength(size_t nbDays)
      {
         if (nbDays == 0)
            return sum(m_trees, 0);

         grow();
         std::sort(begin(m_trees), end(m_trees), reverseComparison(std::less<size_t>()));

         TaroCutting::Ints backUpTrees = m_trees;

         //Start using tree at t...
         size_t min = std::numeric_limits<size_t>::max();
         for (size_t t = 0; t < m_trees.size(); ++t)
         {
            bool didCut = false;
            for (size_t d = 0; d < m_devices.size(); ++d)
            {
               if (t + d >= m_trees.size()) break;
               if (m_devices[d] >= m_trees[t + d]) break;

               m_trees[t + d] = m_devices[d];
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
         for (size_t i = 0; i < m_trees.size(); ++i)
            m_trees[i] += m_growths[i];
      }

      TaroCutting::Ints m_trees;
      TaroCutting::Ints m_growths;
      TaroCutting::Ints m_devices;
   };

   //--------------------------------------------------------------------------

   size_t TaroCutting::minLength(Ints const& trees, Ints const& growths, Ints const& devices, size_t nbDays)
   {
      Cutting cutting(trees, growths, devices);
      return cutting.minLength(nbDays);
   }

   //--------------------------------------------------------------------------

   void taroCuttingTests()
   {
      std::cout << std::endl << "Taro cutting:" << std::endl;
      std::cout << TaroCutting::minLength({ 4, 7 }, { 7, 1 }, { 7 }, 1) << std::endl;
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
   }
}
