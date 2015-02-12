#pragma once
#include "utils/Matrix.h"
#include "utils/Range.h"

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

   /** Find the contiguous sequence with the highest sum value */
   struct MaxContiguous
   {
      using Inputs = std::vector<double>;
      using InputIt = Inputs::const_iterator;

      static Range<InputIt> maxSum(Inputs const&);
      static Range<InputIt> maxProduct(Inputs const&);
   };


   /**
    * Counting the number of ways there are to parenthesize a boolean expression made of True and False
    * to have it return True.
    * Input:
    * - a string made of N booleans: true or false
    * - a vector made of N-1 strings: "or, "and" or "xor"
    * Output:
    * - The number of parenthesization that would make this expression evaluate to True
    */
   struct BooleanParenthesization
   {
      using Variables = std::vector<bool>;
      using Connectors = std::vector<std::string>;

      static size_t count(Variables const& vs, Connectors const& cs);
   };


   /**
    * Zig Zag
    * http://community.topcoder.com/stat?c=problem_statement&pm=1259
    */
   struct ZigZag
   {
      static size_t longest(std::vector<int> const& sequence);
   };

   /**
   * FlowerGarden
   * http://community.topcoder.com/stat?c=problem_statement&pm=1918
   */
   struct FlowerGarden
   {
      using Ints = std::vector<int>;
      static Ints getOrdering(Ints heights, Ints blooms, Ints wilts);
   };


   /**
    * Collecting apples:
    * - some apples are position on the field
    * - a man can only go down and right
    * - the man starts from the top left corner
    * Collect as much appels as possible
    */
   struct CollectingApples
   {
      static size_t findMax(Matrix<size_t> const& field);
   };


   /**
    * Partitioning tasks
    * TODO
    */


   /**
    * Parsing a context free grammar
    * TODO
    */
}
