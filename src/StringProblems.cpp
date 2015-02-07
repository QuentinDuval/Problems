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
      return splits;
   }

   void testWordSplit()
   {
      WordSplit::Dict dict = { "split", "into", "in", "to", "words" };
      WordSplit split(dict);
      auto splits = split.splitInWords("splitintowords");
      for (auto& s : splits)
         std::cout << s << std::endl;
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
