#pragma once

#include "utils/Range.h"
#include <vector>
#include <utility>


namespace prob
{
   struct MaxContiguous
   {
      using Inputs = std::vector<double>;
      using InputIt = Inputs::const_iterator;

      /** Find the contiguous sequence with the highest sum value */
      static Range<InputIt> maxSum(Inputs const&);

      /** Find the contiguous sequence with the highest sum value */
      static Range<InputIt> maxProduct(Inputs const&);
   };

   /** Tests */
   void maxContiguousTest();
}
