#include "ClassicDPProblemsTests.h"
#include "ClassicDPProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>
#include <vector>


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

   //--------------------------------------------------------------------------

   void fiboTests()
   {
      std::vector<size_t> expected{ 0, 1, 1, 2, 3, 5, 8, 13, 21 };
      for (size_t i = 0; i < expected.size(); ++i)
         assert(expected[i] == fibo(i));
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
