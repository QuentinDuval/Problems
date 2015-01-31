#include "utils/Range.h"
#include <vector>
#include <utility>


namespace prob
{
   struct MaxContiguousSum
   {
      using Inputs = std::vector<double>;
      using InputIt = Inputs::const_iterator;

      /** Find the contiguous sequence with the highest sum value */
      static Range<InputIt> find(Inputs const&);
   };

   /** Tests */
   void maxContiguousTest();
}
