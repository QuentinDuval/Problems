#include "ClassicDPProblems.h"
#include "utils/Matrix.h"


namespace prob
{
   size_t binomialCoeff(size_t k, size_t n)
   {
      Matrix<size_t> m(n + 1, n + 1, 1);
      for (size_t i = 1; i <= n; ++i)
         for (size_t j = 1; j < i && j <= k; ++j)
            m.at(j, i) = m.at(j - 1, i - 1) + m.at(j, i - 1);

      return m.at(k, n);
   }

   //--------------------------------------------------------------------------

   size_t editDistance(std::string const& a, std::string const& b)
   {
      if (a.empty()) return b.size();
      if (b.empty()) return a.size();

      Matrix<size_t> distances(a.size() + 1, b.size() + 1);
      for (size_t i = 0; i < a.size(); ++i)
      {
         for (size_t j = 0; j < b.size(); ++j)
         {
            std::vector<size_t> options(3, 0);
            options[0] = distances.at(i, j) + (a[i] != b[j] ? 1 : 0);
            options[1] = distances.at(i, j + 1) + 1;
            options[2] = distances.at(i + 1, j) + 1;
            distances.at(i + 1, j + 1) = *std::min_element(begin(options), end(options));
         }
      }
      return distances.at(a.size(), b.size());
   }

   //--------------------------------------------------------------------------

   size_t fibo(size_t n)
   {
      if (n == 0)
         return 0;

      size_t prev = 0;
      size_t curr = 1;
      for (size_t i = 1; i < n; ++i)
      {
         size_t next = curr + prev;
         prev = curr;
         curr = next;
      }
      return curr;
   }

   /**
   * --------------------------------------------------------------------------
   * Longest[k] = max of:
   * - max { i < k } { input[k] >= Longest[i] } of Longest[i] + 1
   * - max { i < k } { input[k] <  Longest[i] } of Longest[i]
   * --------------------------------------------------------------------------
   */
   std::vector<double> longestIncreasingSeq(std::vector<double> const& inputs)
   {
      size_t len = inputs.size();
      std::vector<size_t> longest(len + 1, 0);
      std::vector<size_t> previous(len + 1, 0);
      std::vector<double> lastVal(len + 1, std::numeric_limits<double>::min());

      for (size_t i = 0; i < len; ++i)
      {
         for (size_t j = 0; j <= i; ++j)
         {
            size_t incr = lastVal[j] > inputs[i] ? 0 : 1;
            if (longest[j] + incr > longest[i + 1])
            {
               previous[i + 1] = j;
               longest[i + 1] = longest[j] + incr;
               lastVal[i + 1] = incr ? inputs[i] : lastVal[j];
            }
         }
      }

      std::vector<double> out;
      for (size_t i = len; i != 0;)
      {
         size_t p = previous[i];
         if (longest[i] > longest[p])
            out.push_back(lastVal[i]);
         i = p;
      }

      std::reverse(begin(out), end(out));
      return out;
   }


   /**
   * --------------------------------------------------------------------------
   * Observation:
   * 1. This looks a lot like the unbounded knapsack problem (in which you can take as many item as you want)
   * 2. The recursion looks then like the one of this classic problem, with the value of item equal to -1
   *
   * Recursion:
   * - makingChange(0) = 0
   * - makingChange(n) = max (k < n) { 1 + makingChange(n - coins[k]) }
   * --------------------------------------------------------------------------
   */
   size_t makingChange(size_t totalAmount, std::vector<size_t> const& coins)
   {
      static const size_t Infinity = std::numeric_limits<size_t>::max();
      std::vector<size_t> changes(totalAmount + 1, Infinity);
      changes[0] = 0;

      for (size_t amount = 1; amount <= totalAmount; ++amount)
      {
         size_t min = Infinity;
         for (size_t i = 0; i < coins.size(); ++i)
         {
            if (amount < coins[i]) break;
            min = std::min(min, 1 + changes[amount - coins[i]]);
         }
         changes[amount] = min;
      }

      return changes[totalAmount];
   }


   /**
   * --------------------------------------------------------------------------
   * Observation:
   * 1. From the standpoint of the value at k, if the sum of a sub-sequence
   * ending at k-1 is negative positive, there is no reason to add it to k.
   * And if positive, there are no reasons not to add it.
   * 2. We need to keep track of the longuest sub-sequence ending at k-1
   * 3. We need to keep track of the longuest sub-sequence as a whole
   *
   * Recurrence relation:
   *
   * Max[k] = max of (
   * - max subsequence of Max[k-1]
   * - max subsuquence of Max[k-1] ending at k-1 + inputs[k]
   * - sub-sequence made of inputs[k] only (or empty sequence if input[k] < 0)
   * )
   * --------------------------------------------------------------------------
   */
   Range<MaxContiguous::InputIt> MaxContiguous::maxSum(std::vector<double> const& inputs)
   {
      double maxValue = 0;
      InputIt maxBeg = begin(inputs);
      InputIt maxEnd = begin(inputs);

      double maxSuffix = 0;
      InputIt maxSuffixBeg = begin(inputs);

      for (auto it = begin(inputs); it != end(inputs); ++it)
      {
         if (0 < maxSuffix)
         {
            maxSuffix += *it;
         }
         else
         {
            maxSuffix = *it;
            maxSuffixBeg = it;
         }

         if (maxSuffix > maxValue)
         {
            maxValue = maxSuffix;
            maxBeg = maxSuffixBeg;
            maxEnd = it + 1;
         }
      }

      return makeRange(maxBeg, maxEnd);
   }

   //--------------------------------------------------------------------------

   Range<MaxContiguous::InputIt> MaxContiguous::maxProduct(Inputs const& inputs)
   {
      Inputs logInputs(inputs.size());
      transform(inputs, logInputs.begin(), [](double d) { return log(d); });
      auto result = maxSum(logInputs);

      auto b = begin(inputs) + std::distance(cbegin(logInputs), begin(result));
      auto e = begin(inputs) + std::distance(cbegin(logInputs), end(result));
      return makeRange(b, e);
   }
}
