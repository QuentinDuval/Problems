#include "LongestIncreasingSeq.h"
#include "utils/Algorithms.h"
#include "utils/Range.h"

#include <assert.h>
#include <limits>


namespace prob
{
   /**
   * Recurrence relation:
   *
   * Longest[k] = max of:
   * - max { i < k } { input[k] >= Longest[i] } of Longest[i] + 1
   * - max { i < k } { input[k] <  Longest[i] } of Longest[i]
   */
   std::vector<double> longestIncreasingSeq(std::vector<double> const& inputs)
   {
      size_t len = inputs.size();
      std::vector<size_t> longest (len + 1, 0);
      std::vector<size_t> previous(len + 1, 0);
      std::vector<double> lastVal (len + 1, std::numeric_limits<double>::min());

      for (size_t i = 0; i < len; ++i)
      {
         for (size_t j = 0; j <= i; ++j)
         {
            size_t incr = lastVal[j] > inputs[i] ? 0 : 1;
            if (longest[j] + incr > longest[i + 1])
            {
               previous[i + 1] = j;
               longest[i + 1]  = longest[j] + incr;
               lastVal[i + 1]  = incr ? inputs[i] : lastVal[j];
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

   //--------------------------------------------------------------------------

   void longestIncreasingSeqTest()
   {
      std::vector<double> increasingSeq = { 1, 2, 3, 4 };
      assert(equal(increasingSeq, longestIncreasingSeq(increasingSeq)));

      std::vector<double> decreasingSeq = { 4, 3, 2, 1 };
      assert(1 == longestIncreasingSeq(decreasingSeq).size());

      std::vector<double> standardSeq = { 9, 1, 5, 2, 10, 4, 4, 5, -1, 11 };
      std::vector<double> expected = { 1, 2, 4, 4, 5, 11 };
      assert(equal(expected, longestIncreasingSeq(standardSeq)));
   }
}
