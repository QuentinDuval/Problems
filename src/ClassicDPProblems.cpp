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
}
