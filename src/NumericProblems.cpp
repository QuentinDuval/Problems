#include "NumericProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"
#include <functional>


namespace prob
{
   /**
    * Lun the dog will always by the cheapest apple.
    * We need to keep track of what price was the last apple he bought.
    */
   static const int MOD = 1000000007;
   using ModPrice = std::pair<int, int>;

   static ModPrice makeModPrice(int i)
   {
      return std::make_pair(i / MOD, i % MOD);
   }

   static void doubleModPrice(ModPrice& p)
   {
      p.second *= 2;
      if (p.second < MOD)
         return;

      p.first++;
      p.second = p.second % MOD;
   }

   int KitayutaMart::lastPrice(int n, int k)
   {
      std::vector<ModPrice> prices(k);
      for (int i = 0; i < k; ++i)
         prices[i] = makeModPrice(i + 1);

      long long mostExpensive = 0;
      auto comp = std::greater<ModPrice>();
      std::make_heap(begin(prices), end(prices), comp);

      for (int i = 0; i < n; ++i)
      {
         std::pop_heap(begin(prices), end(prices), comp);
         mostExpensive = prices.back().second;
         doubleModPrice(prices.back());
         std::push_heap(begin(prices), end(prices), comp);
      }

      return mostExpensive;
   }
}
