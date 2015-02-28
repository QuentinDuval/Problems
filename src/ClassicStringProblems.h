#pragma once

#include <string>
#include <vector>


namespace prob
{
   /** Find the first character that does not appear anywhere else in the string */
   std::pair<bool, char> firstNonRepeatedChar(std::string const& str);

   /** Remove some characters from a string */
   void removeChars(std::string& str, std::string const& toRemove);
   void removeCharsManual(std::string& str, std::string const& toRemove);

   /** Reverse the words making the string */
   void reverseWords(std::string& str);

   /** Return all the permutations / combinations of a string */
   std::vector<std::string> permutations(std::string const& str);
   std::vector<std::string> combinations(std::string const& str);
}
