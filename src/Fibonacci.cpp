#include "Fibonacci.h"

#include <assert.h>
#include <vector>


namespace prob
{
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

   void fiboTests()
   {
      std::vector<size_t> expected{ 0, 1, 1, 2, 3, 5, 8, 13, 21 };
      for (size_t i = 0; i < expected.size(); ++i)
         assert(expected[i] == fibo(i));
   }
}
