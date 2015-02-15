#pragma once

#include <vector>


namespace prob
{
   /** http://community.topcoder.com/stat?c=problem_statement&pm=13649 */
   struct KitayutaMart
   {
      static int lastPrice(int n, int k);
   };

   /**
    * TheKingsFactorization
    * http://community.topcoder.com/stat?c=problem_statement&pm=13594
    */
   struct TheKingsFactorization
   {
      static std::vector<long> getVector(long n, std::vector<long> const& primes);
   };
}
