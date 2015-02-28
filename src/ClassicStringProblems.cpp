#include "ClassicStringProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <iterator>
#include <set>
#include <unordered_set>


namespace prob
{
   std::pair<bool, char> firstNonRepeatedChar(std::string const& str)
   {
      std::vector<int> counts(UCHAR_MAX + 1, 0);
      for (char c : str)
         counts.at(c - CHAR_MIN) += 1;

      for (char c : str)
      {
         if (counts.at(c - CHAR_MIN) == 1)
            return std::make_pair(true, c);
      }
      return std::make_pair(false, ' ');
   }

   //--------------------------------------------------------------------------

   void removeChars(std::string& str, std::string const& toRemove)
   {
      std::unordered_set<char> charSet;
      std::copy(begin(toRemove), end(toRemove), std::inserter(charSet, begin(charSet)));
      auto last = std::remove_if(begin(str), end(str), [&charSet](char c){ return end(charSet) != charSet.find(c); });
      str.erase(last, end(str));
   }

   void removeCharsManual(std::string& str, std::string const& toRemove)
   {
      std::unordered_set<char> charSet;
      std::copy(begin(toRemove), end(toRemove), std::inserter(charSet, begin(charSet)));

      std::string::iterator valid = begin(str);
      for (size_t i = 0; i < str.size(); ++i)
      {
         char c = str.at(i);
         if (end(charSet) != charSet.find(c))
            continue;

         *valid = c;
         ++valid;
      }
      str.erase(valid, end(str));
   }

   //--------------------------------------------------------------------------

   void reverseWords(std::string& str)
   {
      std::reverse(begin(str), end(str));
      auto start = begin(str);
      for (auto last = begin(str); last != end(str); ++last)
      {
         if (*last == ' ')
         {
            std::reverse(start, last);
            start = last + 1;
         }
      }

      if (start != end(str))
      {
         std::reverse(start, end(str));
      }
   }
}
