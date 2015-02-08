#pragma once

#include <string>
#include <vector>


namespace prob
{
   /**
    * With 2 coins of value 2^K for each K, find the number of ways you can represent a number N.
    * http://community.topcoder.com/stat?c=problem_statement&pm=12856
    */
   long taroCoins(long long n);


   /**
    * Input: a vector of N strings of length N, representing lines.
    * Each string is filled with either W or B (white or black).
    * Output: longest sequence inside a column of consecutive W or B.
    * http://community.topcoder.com/stat?c=problem_statement&pm=13394
    */
   size_t taroGrid(std::vector<std::string> const&);


   /**
    * TaroCutting
    * http://community.topcoder.com/stat?c=problem_statement&pm=13319
    */
   struct TaroCutting
   {
      using Ints = std::vector<size_t>;
      static size_t minLength(Ints const& heights, Ints const& growths, Ints const& deviceSizes, size_t nbDays);
   };
}
