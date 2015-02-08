#pragma once

#include <string>
#include <vector>


namespace prob
{
   size_t binomialCoeff(size_t k, size_t n);
   size_t editDistance(std::string const& a, std::string const& b);
   size_t fibo(size_t n);
   std::vector<double> longestIncreasingSeq(std::vector<double> const&);
}
