#include "BinomialCoeff.h"
#include "utils/Matrix.h"

#include <assert.h>


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
}
