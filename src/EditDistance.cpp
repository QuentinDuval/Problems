#include "EditDistance.h"
#include "utils/Matrix.h"

#include <algorithm>
#include <assert.h>
#include <iostream>


namespace prob
{
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

   void editDistanceTests()
   {
      assert(0 == editDistance("", ""));
      assert(2 == editDistance("", "ab"));
      assert(2 == editDistance("ab", ""));
      assert(0 == editDistance("ab", "ab"));

      assert(1 == editDistance("ab", "abc"));
      assert(1 == editDistance("abc", "ab"));
      assert(1 == editDistance("abc", "abd"));

      std::cout << "Edit distance: " << editDistance("I misspelt mine sentense", "I misspelled my sentence") << std::endl;
   }
}
