#pragma once

#include <string>
#include <unordered_set>
#include <vector>


namespace prob
{
   class WordSplit
   {
   public:
      using Dict = std::unordered_set<std::string>;

   public:
      WordSplit(Dict const& dict);
      ~WordSplit() = default;

      /**
       * Provided a string as input, split it with words in the dictionary
       * If several possibilities might exist, it will return one of them.
       */
      std::vector<std::string> splitInWords(std::string const&);

   private:
      Dict const& m_dict;
   };

   void testWordSplit();
}
