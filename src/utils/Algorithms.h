#pragma once

#include <algorithm>
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

   template<typename Container, typename Output, typename Tranformation>
   Output transform(Container& c, Output out, Tranformation tf)
   {
      return std::transform(begin(c), end(c), out, tf);
   }

   template<typename Container, typename Container2, typename Output, typename Tranformation>
   Output zipWith(Container& c, Container2& c2, Output out, Tranformation tf)
   {
      return std::transform(begin(c), end(c), begin(c2), out, tf);
   }

   //--------------------------------------------------------------------------

   template<typename Container, typename Less>
   void sortBy(Container& cont, Less less)
   {
      std::sort(begin(cont), end(cont), less);
   }

   //--------------------------------------------------------------------------

   template<typename Container, typename Less>
   typename Container::const_iterator minBy(Container const& cont, Less less)
   {
      return std::min_element(begin(cont), end(cont), less);
   }

   template<typename Container, typename Less>
   typename Container::const_iterator maxBy(Container const& cont, Less less)
   {
      return std::max_element(begin(cont), end(cont), less);
   }

   //--------------------------------------------------------------------------

   template<typename Container, typename Container2>
   bool equal(Container const& cont, Container2 cont2)
   {
      return std::equal(begin(cont), end(cont), begin(cont2));
   }

   //--------------------------------------------------------------------------

   template<typename Container, typename Val>
   bool contains(Container const& cont, Val val)
   {
      return end(cont) != std::find(begin(cont), end(cont), val);
   }

   template<typename Container, typename Predicate>
   bool containsIf(Container const& cont, Predicate pred)
   {
      return end(cont) != std::find_if(begin(cont), end(cont), pred);
   }

   //--------------------------------------------------------------------------

   template<typename Container, typename Val>
   void erase(Container& cont, Val const& v)
   {
      auto it = std::remove(begin(cont), end(cont), v);
      cont.erase(it, end(cont));
   }

   template<typename Container, typename Predicate>
   void eraseIf(Container& cont, Predicate p)
   {
      auto it = std::remove_if(begin(cont), end(cont), p);
      cont.erase(it, end(cont));
   }

   //--------------------------------------------------------------------------

   template<typename Container, typename Val, typename Acc>
   Val accumulate(Container& c, Val const& v, Acc acc)
   {
      return std::accumulate(begin(c), end(c), v, acc);
   }

   template<typename Container, typename Output, typename Val>
   void intersperse(Container& cont, Output out, Val const& v)
   {
      bool first = true;
      for (auto& c : cont)
      {
         if (!first)
         {
            *out = v;
            ++out;
         }

         first = false;
         *out = c;
         ++out;
      }
   }

   template<typename Container, typename Val>
   Val sum(Container& c, Val const& v)
   {
      return accumulate(c, v, std::plus<Val>());
   }

   template<typename Container, typename Val>
   Val product(Container& c, Val const& v)
   {
      return accumulate(c, v, std::multiplies<Val>());
   }
}
