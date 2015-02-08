#include "StringProblemsTests.h"
#include "StringProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void StringProblemsTests::allTests()
   {
      testWordSplit();
      doubleLetterTests();
      parenthesesCombinationNbTests();
      bracketExpressionsTests();
      taroStringTests();
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::testWordSplit()
   {
      WordSplit::Dict dict = { "split", "into", "in", "to", "words" };
      WordSplit split(dict);

      assert(true == split.splitInWords("splitintoword").empty());
      assert(4 == split.splitInWords("splitintowords").size());
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::doubleLetterTests()
   {
      assert(true == doubleLetter("aabccb"));
      assert(false == doubleLetter("aabccbb"));
      assert(true == doubleLetter("abcddcba"));
      assert(false == doubleLetter("abab"));
      assert(true == doubleLetter("aaaaaaaaaa"));
      assert(false == doubleLetter("aababbabbaba"));
      assert(true == doubleLetter("zzxzxxzxxzzx"));
   }

   //--------------------------------------------------------------------------
   
   void StringProblemsTests::parenthesesCombinationNbTests()
   {
      assert(0 == Parentheses::combinationNb(0).size());
      assert(1 == Parentheses::combinationNb(1).size());
      assert(2 == Parentheses::combinationNb(2).size());
      assert(4 == Parentheses::combinationNb(3).size());

      std::vector<std::string> toShow;
      auto result = Parentheses::combinationNb(4);
      intersperse(result, std::back_inserter(toShow), ", ");
      std::cout << sum(toShow, std::string("")) << std::endl;
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::bracketExpressionsTests()
   {
      assert(true == BracketExpressions::isPossible(""));
      assert(true == BracketExpressions::isPossible("([]{})"));
      assert(true == BracketExpressions::isPossible("(())[]"));
      assert(true == BracketExpressions::isPossible("({X)"));
      assert(false == BracketExpressions::isPossible("({])"));
      assert(false == BracketExpressions::isPossible("[]X"));
      assert(true == BracketExpressions::isPossible("([]X()[()]XX}[])X{{}}]"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::taroStringTests()
   {
      assert(true == TaroString::getAnswer("XCYAZTX"));
      assert(false == TaroString::getAnswer("CTA"));
      assert(false == TaroString::getAnswer("ACBBAT"));
      assert(true == TaroString::getAnswer("SGHDJHFIOPUFUHCHIOJBHAUINUIT"));
      assert(false == TaroString::getAnswer("CCCATT"));
   }
}
