#pragma once
#include <numeric>


namespace prob
{
   template<typename Container, typename Val, typename Acc>
   Val accumulate(Container& c, Val const& v, Acc acc)
   {
      return std::accumulate(begin(c), end(c), v, acc);
   }

   template<typename Container, typename Val>
   Val sum(Container& c, Val const& v)
   {
      return accumulate(c, v, std::plus<Val>());
   }
}
