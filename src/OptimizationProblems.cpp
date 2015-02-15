#include "OptimizationProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"


namespace prob
{
   int JumpFurther::furthest(int N, int badStep)
   {
      int furthest = 0;
      for (int jump = 1; jump <= N; ++jump)
      {
         furthest += jump;
         if (furthest == badStep)
            furthest -= 1; //do not jump first step
      }
      return furthest;
   }


   //--------------------------------------------------------------------------
   // TheConsecutiveIntegersDivOne:
   // - The order does not matter => sorting
   // - Then find the set [i..i+k-1] with the minimum difference between them
   // - The result is then:
   //   (dist[i, i+1] - 1) + 2 * (dist[i+1, i+2] - 1) + ...
   //                      + 2 * (dist[i+k-3, i+k-2] - 1) + (dist[i+k-2, i+k-1] - 1)
   //--------------------------------------------------------------------------

   int TheConsecutiveIntegersDivOne::find(std::vector<int> const& numbers, int k)
   {
      if (k < 2)
         return 0;

      std::vector<int> sortedNbs(numbers);
      std::sort(begin(sortedNbs), end(sortedNbs));

      int minDist = std::numeric_limits<int>::max();
      for (size_t start = 0; start < sortedNbs.size() - k; ++start)
      {
         int dist = 0;
         for (size_t j = start + 1; j < start + k; ++j)
         {
            int added = sortedNbs[j] - sortedNbs[j - 1] - 1;
            dist += added * std::min(j - start, start + k - j);
         }
         minDist = std::min(minDist, dist);
      }

      return minDist;
   }
}
