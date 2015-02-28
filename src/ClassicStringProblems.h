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
}
