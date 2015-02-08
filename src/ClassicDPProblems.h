#pragma once

#include <string>
#include <vector>


namespace prob
{
   size_t binomialCoeff(size_t k, size_t n);
   size_t editDistance(std::string const& a, std::string const& b);
   size_t fibo(size_t n);

   /** Find the longest sub-sequence of increasing numbers */
   std::vector<double> longestIncreasingSeq(std::vector<double> const&);

   /**
    * Find the minimum amount of coins needed to exchange the amount with the given coin values.
    * The coin values are strictly increasing and higher than 1 as we assume with have the coin 1 by default.
    */
   size_t makingChange(size_t amount, std::vector<size_t> const& coinValues);
}
