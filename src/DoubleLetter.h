#pragma once

#include <string>


namespace prob
{
   /**
    * Eliminate double letters starting from the leftmost occurence.
    * Repeat as long as double letters can be found and return if the string is empty.
    * http://community.topcoder.com/stat?c=problem_statement&pm=13378
    */
   bool doubleLetter(std::string const&);

   void doubleLetterTests();
}
