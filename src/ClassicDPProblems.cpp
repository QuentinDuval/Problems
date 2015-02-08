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
}
