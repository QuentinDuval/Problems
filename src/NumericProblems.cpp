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
   int KitayutaMart::lastPrice(int n, int k)
   {
      std::vector<long long> prices(k, 0);
      for (int i = 0; i < k; ++i)
         prices[i] = i + 1;

      long long mostExpensive = 0;
      auto comp = std::greater<int>();
      std::make_heap(begin(prices), end(prices), comp);

      for (int i = 0; i < n; ++i)
      {
         std::pop_heap(begin(prices), end(prices), comp);
         mostExpensive = prices.back();
         prices.back() *= 2;
         std::push_heap(begin(prices), end(prices), comp);
      }

      return mostExpensive % 1000000007;
   }
}
