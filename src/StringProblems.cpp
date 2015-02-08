#include "StringProblems.h"
#include "utils/Matrix.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   WordSplit::WordSplit(Dict const& dict)
      : m_dict(dict)
   {}

   std::vector<std::string> WordSplit::splitInWords(std::string const& input)
   {
      size_t lastSplit = 0;
      std::vector<std::string> splits;

      for (size_t i = 1; i <= input.size(); ++i)
      {
         std::string temp(input.begin() + lastSplit, input.begin() + i);
         if (m_dict.find(temp) != end(m_dict))
         {
            lastSplit = i;
            splits.emplace_back(std::move(temp));
         }
      }

      if (lastSplit != input.size())
         return std::vector<std::string>();
      return splits;
   }

   void testWordSplit()
   {
      WordSplit::Dict dict = { "split", "into", "in", "to", "words" };
      WordSplit split(dict);

      assert(true == split.splitInWords("splitintoword").empty());
      assert(4 == split.splitInWords("splitintowords").size());
   }


   //--------------------------------------------------------------------------
   // Parentheses
   //--------------------------------------------------------------------------

   std::vector<std::string> Parentheses::combinationNb(size_t nbPairs)
   {
      std::vector<std::string> combinations;
      if (nbPairs == 0) return combinations;
      if (nbPairs == 1) return { "()" };

      for (auto&s : combinationNb(nbPairs - 1))
      {
         combinations.push_back(s + "()");
         combinations.push_back("(" + s + ")");
      }
      return combinations;
   }
   
   void Parentheses::testCombinationNb()
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
   // TARO STRING
   //--------------------------------------------------------------------------

   static const char* possible = "\"Possible\"";
   static const char* impossible = "\"Impossible\"";

   std::string TaroString::getAnswer(std::string const& s)
   {
      std::string cleanedS = s;
      eraseIf(cleanedS, [](char c){ return c != 'C' && c != 'A' && c != 'T'; });
      return cleanedS == "CAT" ? possible : impossible;
   }

   void TaroString::tests()
   {
      assert(possible == TaroString::getAnswer("XCYAZTX"));
      assert(impossible == TaroString::getAnswer("CTA"));
      assert(impossible == TaroString::getAnswer("ACBBAT"));
      assert(possible == TaroString::getAnswer("SGHDJHFIOPUFUHCHIOJBHAUINUIT"));
      assert(impossible == TaroString::getAnswer("CCCATT"));
   }
}
