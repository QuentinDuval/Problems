#include "MakingChange.h"

#include <algorithm>
#include <assert.h>
#include <limits>


namespace prob
{
   /**
   * Observation:
   * 1. This looks a lot like the unbounded knapsack problem (in which you can take as many item as you want)
   * 2. The recursion looks then like the one of this classic problem, with the value of item equal to 1
   *
   * Recursion:
   * - makingChange(0) = 0
   * - makingChange(n) = max (k < n) { 1 + makingChange(n - coins[k]) }
   */
   size_t makingChange(size_t totalAmount, std::vector<size_t> const& coins)
   {
      static const size_t Infinity = std::numeric_limits<size_t>::max();
      std::vector<size_t> changes(totalAmount + 1, Infinity);
      changes[0] = 0;
      
      for (size_t amount = 1; amount <= totalAmount; ++amount)
      {
         size_t min = Infinity;
         for (size_t i = 0; i < coins.size(); ++i)
         {
            if (amount < coins[i]) break;
            min = std::min(min, 1 + changes[amount - coins[i]]);
         }
         changes[amount] = min;
      }

      return changes[totalAmount];
   }

   //--------------------------------------------------------------------------

   void makingChangeTests()
   {
      assert(1 == makingChange(1, { 1 }));
      assert(5 == makingChange(5, { 1 }));
      assert(3 == makingChange(5, { 1, 2 }));
      assert(19 == makingChange(123, { 1, 3, 5, 7 }));
   }
}
