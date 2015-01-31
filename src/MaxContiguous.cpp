#include "MaxContiguous.h"

#include <iostream>


namespace prob
{
   /**
   * Observation:
   * 1. From the standpoint of the value at k, if the sum of a sub-sequence
   * ending at k-1 is negative positive, there is no reason to add it to k.
   * And if positive, there are no reasons not to add it.
   * 2. We need to keep track of the longuest sub-sequence ending at k-1
   * 3. We need to keep track of the longuest sub-sequence as a whole
   *
   * Recurrence relations:
   *
   * Max[k] = max of (
   * - max subsequence of Max[k-1]
   * - max subsuquence of Max[k-1] ending at k-1 + inputs[k]
   * - sub-sequence made of inputs[k] only (or empty sequence if input[k] < 0)
   * )
   */
   Range<MaxContiguousSum::InputIt> MaxContiguousSum::find(std::vector<int> const& inputs)
   {
      int maxValue = 0;
      InputIt maxBeg = begin(inputs);
      InputIt maxEnd = begin(inputs);

      int maxSuffix = 0;
      std::vector<int>::const_iterator maxSuffixBeg = begin(inputs);

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


   void maxContiguousTest()
   {
      std::vector<int> inputs = { 1, -1, 2, 3, 2, -7, 2, 5, -5, 10 };
      auto result = MaxContiguousSum::find(inputs);
      for (auto& r : result)
         std::cout << r << std::endl;
   }
}
