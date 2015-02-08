#include "ClassicDPProblemsTests.h"
#include "ClassicDPProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>
#include <vector>


namespace prob
{
   void ClassicDPProblemsTests::allTests()
   {
      binomialCoeffTests();
      editDistanceTests();
      fiboTests();
      longestIncreasingSeqTest();
      makingChangeTests();
      maxContiguousTest();
      boolParenthesizationTest();
   }

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::binomialCoeffTests()
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

   void ClassicDPProblemsTests::editDistanceTests()
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

   void ClassicDPProblemsTests::fiboTests()
   {
      std::vector<size_t> expected{ 0, 1, 1, 2, 3, 5, 8, 13, 21 };
      for (size_t i = 0; i < expected.size(); ++i)
         assert(expected[i] == fibo(i));
   }

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::longestIncreasingSeqTest()
   {
      std::vector<double> increasingSeq = { 1, 2, 3, 4 };
      assert(equal(increasingSeq, longestIncreasingSeq(increasingSeq)));

      std::vector<double> decreasingSeq = { 4, 3, 2, 1 };
      assert(1 == longestIncreasingSeq(decreasingSeq).size());

      std::vector<double> standardSeq = { 9, 1, 5, 2, 10, 4, 4, 5, -1, 11 };
      std::vector<double> expected = { 1, 2, 4, 4, 5, 11 };
      assert(equal(expected, longestIncreasingSeq(standardSeq)));
   }

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::makingChangeTests()
   {
      assert(1 == makingChange(1, { 1 }));
      assert(5 == makingChange(5, { 1 }));
      assert(3 == makingChange(5, { 1, 2 }));
      assert(19 == makingChange(123, { 1, 3, 5, 7 }));
   }

   //--------------------------------------------------------------------------

   static void maxContiguousSumTest()
   {
      std::vector<double> allPositive(10, 1);
      auto expected = makeRange(cbegin(allPositive), cend(allPositive));
      assert(expected == MaxContiguous::maxSum(allPositive));

      std::vector<double> allNegative(10, -1);
      assert(MaxContiguous::maxSum(allNegative).empty());

      std::vector<double> oscillator(10, -1);
      generate(oscillator, -1., [](double d) { return -d; });
      assert(1 == MaxContiguous::maxSum(oscillator).size());

      std::vector<double> stdInputs = { 1, -1, 2, 3, 2, -7, 2, 5, -5, 10 };
      assert(12 == sum(MaxContiguous::maxSum(stdInputs), 0.));
   }

   static void maxContiguousProdTest()
   {
      std::vector<double> allOnes(10, 1);
      assert(1. == product(MaxContiguous::maxProduct(allOnes), 1.));

      std::vector<double> stdInputs = { 1, 0.87, 0.5, 1.1, 2, 0.9, 5, 0.5, 1.1 };
      for (auto& r : MaxContiguous::maxProduct(stdInputs))
         std::cout << r << std::endl;
   }

   void ClassicDPProblemsTests::maxContiguousTest()
   {
      maxContiguousSumTest();
      maxContiguousProdTest();
   }

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::boolParenthesizationTest()
   {
      for (auto& s : { "or", "and" })
         assert(1 == BooleanParenthesization::count({ true, true }, { s }));
      assert(0 == BooleanParenthesization::count({ true, true }, { "xor" }));

      for (auto& s : { "or", "xor" })
         assert(1 == BooleanParenthesization::count({ true, false }, { s }));
      assert(0 == BooleanParenthesization::count({ true, false }, { "and" }));

      for (auto& s : { "or", "xor", "and" })
         assert(0 == BooleanParenthesization::count({ false, false }, { s }));

      BooleanParenthesization::Variables vs = { true, false, true, true };
      BooleanParenthesization::Connectors cs = { "or", "and", "xor" };
      assert(2 == BooleanParenthesization::count(vs, cs));
      
      vs = { true, false, true, true, false };
      cs = { "or", "and", "xor", "and" };
      std::cout << "Bool (): " << BooleanParenthesization::count(vs, cs) << std::endl;
   }
}
