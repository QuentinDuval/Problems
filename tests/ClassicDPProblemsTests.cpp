#include "ClassicDPProblemsTests.h"
#include "ClassicDPProblems.h"
#include "utils/Algorithms.h"
#include "utils/Matrix.h"

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
      optimalGameStrategyTests();
      zigZagTests();
      flowerGardenTests();
      collectingAppleTests();
      partitioningTests();
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

      std::vector<double> ccInputs = { 2, -8, 3, -2, 4, -10 };
      assert(5 == sum(MaxContiguous::maxSum(ccInputs), 0.));
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

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::optimalGameStrategyTests()
   {
      OptimalGameStrategy::Coins coins = { 1, 2, 1, 3, 1, 2, 1, 1 };
      assert(8 == OptimalGameStrategy::bestScore(coins));
      assert(4 == OptimalGameStrategy::bestDifferential(coins));
   }

   //--------------------------------------------------------------------------
   
   void ClassicDPProblemsTests::zigZagTests()
   {
      assert(6 == ZigZag::longest({ 1, 7, 4, 9, 2, 5 }));
      assert(7 == ZigZag::longest({ 1, 17, 5, 10, 13, 15, 10, 5, 16, 8 }));
      assert(1 == ZigZag::longest({ 44 }));
      assert(2 == ZigZag::longest({ 1, 2, 3, 4, 5, 6, 7, 8, 9 }));
      assert(8 == ZigZag::longest({ 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 }));
      assert(36 == ZigZag::longest(
      { 374, 40, 854, 203, 203, 156, 362, 279, 812, 955,
        600, 947, 978, 46, 100, 953, 670, 862, 568, 188,
        67, 669, 810, 704, 52, 861, 49, 640, 370, 908,
        477, 245, 413, 109, 659, 401, 483, 308, 609, 120,
        249, 22, 176, 279, 23, 22, 617, 462, 459, 244 }));
   }

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::flowerGardenTests()
   {
      auto res0 = FlowerGarden::getOrdering({ 5, 4, 3, 2, 1 }, {1, 1, 1, 1, 1}, {365, 365, 365, 365, 365});
      assert(equal(FlowerGarden::Ints{ 1, 2, 3, 4, 5 }, res0));

      auto res1 = FlowerGarden::getOrdering({ 5, 4, 3, 2, 1 }, {1, 5, 10, 15, 20}, {4, 9, 14, 19, 24});
      assert(equal(FlowerGarden::Ints{ 5, 4, 3, 2, 1 }, res1));

      auto res2 = FlowerGarden::getOrdering({ 5, 4, 3, 2, 1 }, {1, 5, 10, 15, 20}, {5, 10, 15, 20, 25});
      assert(equal(FlowerGarden::Ints{ 1, 2, 3, 4, 5 }, res2));

      auto res3 = FlowerGarden::getOrdering({ 5, 4, 3, 2, 1 }, {1, 5, 10, 15, 20}, {5, 10, 14, 20, 25});
      assert(equal(FlowerGarden::Ints{ 3, 4, 5, 1, 2 }, res3));

      auto res4 = FlowerGarden::getOrdering({ 1, 2, 3, 4, 5, 6 }, {1, 3, 1, 3, 1, 3}, {2, 4, 2, 4, 2, 4});
      assert(equal(FlowerGarden::Ints{ 2, 4, 6, 1, 3, 5 }, res4));

      auto res5 = FlowerGarden::getOrdering({ 3, 2, 5, 4 }, {1, 2, 11, 10}, {4, 3, 12, 13});
      assert(equal(FlowerGarden::Ints{ 4, 5, 2, 3 }, res5));
   }

   //--------------------------------------------------------------------------
   
   void ClassicDPProblemsTests::collectingAppleTests()
   {
      assert(3 == CollectingApples::findMax(Matrix<size_t>(2, 2, { 1, 1, 1, 1 })));
      assert(4 == CollectingApples::findMax(Matrix<size_t>(2, 2, { 1, 2, 1, 1 })));
      assert(11 == CollectingApples::findMax(Matrix<size_t>(4, 4, {
         0, 2, 1, 1,
         0, 2, 1, 5,
         0, 2, 0, 0,
         0, 2, 1, 1
      })));
   }

   //--------------------------------------------------------------------------

   void ClassicDPProblemsTests::partitioningTests()
   {
      auto res1 = TaskPartitioning::find({ 100, 200, 300, 500 }, 2);
      assert(1 == res1.size());
      assert(2 == res1[0]);

      auto res2 = TaskPartitioning::find({ 100, 200, 300, 500, 400, 100 }, 3);
      assert(2 == res2.size());
      assert(2 == res2[0]);
      assert(3 == res2[1]);
   }
}
