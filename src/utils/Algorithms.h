#pragma once
#include <numeric>


namespace prob
{
   template<typename FwdIter, typename ValueType, typename NextFct>
   void generate(FwdIter first, FwdIter last, ValueType const& val, NextFct next)
   {
      for (auto nextVal = val; first != last; ++first)
      {
         *first = nextVal;
         nextVal = next(nextVal);
      }
   }

   template<typename Container, typename ValueType, typename NextFct>
   void generate(Container& cont, ValueType const& val, NextFct next)
   {
      generate(begin(cont), end(cont), val, next);
   }

   //--------------------------------------------------------------------------

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
