#include "NumericProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"
#include <functional>


namespace prob
{
   /**
    * -------------------------------------------------------------------------
    * Observation:
    * -------------------------------------------------------------------------
    *
    * Lun the dog will always by the cheapest apple.
    * We need to keep track of what price was the last apple he bought.
    *
    * Because the price goes from 1 to K one by one, before reaching the point where
    * the Kth price is the stricly lowest price, we need to buy: K + K/2 + ... + 1 apples.
    * So before reaching K:
    * - after 1 buy, the prices goes up by 1
    * - after 2 additional buys, the prices goes up by 1
    * - etc.
    * 
    * After this first time buying the Kth value, all values are comprised between ]K, 2*K].
    * So each period between a doubling of all values will be of exactly K buys.
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
