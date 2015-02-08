#include "ClassicDPProblemsTests.h"
#include "ClassicDPProblems.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void binomialCoeffTests()
   {
      for (size_t n = 1; n < 10; ++n)
      {
         assert(1 == binomialCoeff(0, n));
         assert(1 == binomialCoeff(n, n));
      }

      assert(2 == binomialCoeff(1, 2));
      assert(3 == binomialCoeff(1, 3));
      assert(3 == binomialCoeff(2, 3));
      assert(6 == binomialCoeff(2, 4));
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
