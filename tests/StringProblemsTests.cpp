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
      wolfDelaymasterTests();
      ipv444Tests();
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

   //--------------------------------------------------------------------------

   void StringProblemsTests::wolfDelaymasterTests()
   {
      assert(true == WolfDelaymaster::isValid("wolf"));
      assert(false == WolfDelaymaster::isValid("wwolfolf"));
      assert(true == WolfDelaymaster::isValid("wolfwwoollffwwwooolllfffwwwwoooollllffff"));
      assert(false == WolfDelaymaster::isValid("flowolf"));
   }

   //--------------------------------------------------------------------------

   static void ipv444ParsingTests()
   {
      IPv444::Addr addr = IPv444::parseAddress("123.25.7.986");
      assert(123 == addr[0]);
      assert(25 == addr[1]);
      assert(7 == addr[2]);
      assert(986 == addr[3]);

      addr = IPv444::parseAddress("0.1.*.*");
      assert(0 == addr[0]);
      assert(1 == addr[1]);
      assert(1000 == addr[2]);
      assert(1000 == addr[3]);
   }

   void StringProblemsTests::ipv444Tests()
   {
      ipv444ParsingTests();
   }
}
