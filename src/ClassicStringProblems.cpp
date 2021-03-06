#include "ClassicStringProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <array>
#include <iterator>
#include <set>
#include <unordered_map>
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

   //--------------------------------------------------------------------------

   static void permutationsRec(std::string& str, std::string::iterator current, std::vector<std::string>& output)
   {
      if (current == end(str))
         return;

      if (1 == std::distance(current, end(str)))
      {
         output.push_back(str);
         return;
      }

      for (auto it = current; it != end(str); ++it)
      {
         std::swap(*it, *current);
         permutationsRec(str, current + 1, output);
         std::swap(*it, *current);
      }
   }

   std::vector<std::string> permutations(std::string const& s)
   {
      std::string str(s);
      std::vector<std::string> result;
      permutationsRec(str, begin(str), result);
      return result;
   }

   //--------------------------------------------------------------------------

   static std::vector<std::string> combinationsRec(std::string::const_iterator first, std::string::const_iterator last)
   {
      std::vector<std::string> results;
      if (first == last)
         return results;

      results.emplace_back(1, *first);
      auto recResults = combinationsRec(first + 1, last);
      for (auto& s : recResults)
      {
         results.push_back(s);
         results.push_back(*first + s);
      }
      return results;
   }

   std::vector<std::string> combinations(std::string const& str)
   {
      return combinationsRec(begin(str), end(str));
   }

   //--------------------------------------------------------------------------

   static char getCharKey(int telephoneKey, int index)
   {
      static std::unordered_map<int, std::vector<char>> charMap = {
            { 2, { 'A', 'B', 'C' } },
            { 3, { 'D', 'E', 'F' } },
            { 4, { 'G', 'H', 'I' } },
            { 5, { 'J', 'K', 'L' } },
            { 6, { 'M', 'N', 'O' } },
            { 7, { 'P', 'R', 'S' } },
            { 8, { 'T', 'U', 'V' } },
            { 9, { 'W', 'X', 'Y' } }
      };
      return charMap[telephoneKey][index - 1];
   }

   static std::vector<char> representents(char digit)
   {
      static std::array<char, 8> withLetters = { '2', '3', '4', '5', '6', '7', '8', '9' };
      if (end(withLetters) == std::find(begin(withLetters), end(withLetters), digit))
         return std::vector<char>(1, digit);

      std::vector<char> repr(3);
      for (int i : { 1, 2, 3})
      {
         repr[i - 1] = getCharKey(digit - '0', i);
      }
      return repr;
   }

   static void phoneWords(std::string const& phoneNb, std::string& partialWord, size_t curr, std::vector<std::string>& words)
   {
      if (curr == phoneNb.size())
      {
         words.push_back(partialWord);
         return;
      }

      for (char c : representents(phoneNb[curr]))
      {
         partialWord.push_back(c);
         phoneWords(phoneNb, partialWord, curr + 1, words);
         partialWord.pop_back();
      }
   }

   std::vector<std::string> phoneWords(std::string const& phoneNb)
   {
      std::vector<std::string> words;
      std::string partialWord;
      phoneWords(phoneNb, partialWord, 0, words);
      return words;
   }
}
