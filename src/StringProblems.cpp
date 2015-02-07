#include "StringProblems.h"
#include "utils/Matrix.h"

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

   //--------------------------------------------------------------------------

   void testWordSplit()
   {
      WordSplit::Dict dict = { "split", "into", "in", "to", "words" };
      WordSplit split(dict);
      auto splits = split.splitInWords("splitintowords");
      for (auto& s : splits)
         std::cout << s << std::endl;
   }
}
