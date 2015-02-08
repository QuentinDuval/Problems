#pragma once

#include <string>
#include <unordered_set>
#include <vector>


namespace prob
{
   /**
   * Provided a string as input, split it with words in the dictionary
   * If several possibilities might exist, it will return one of them.
   */
   class WordSplit
   {
   public:
      using Dict = std::unordered_set<std::string>;

      WordSplit(Dict const& dict);
      std::vector<std::string> splitInWords(std::string const&);

   private:
      Dict const& m_dict;
   };


   /**
   * Eliminate double letters starting from the leftmost occurence.
   * Repeat as long as double letters can be found and return if the string is empty.
   * http://community.topcoder.com/stat?c=problem_statement&pm=13378
   */
   bool doubleLetter(std::string const&);

   /**
   * Provided a number of parenthesis pairs input, return the different string possible.
   * Ex: 2 should yield 2 possibilities "()()" and "(())".
   */
   struct Parentheses
   {
      static std::vector<std::string> combinationNb(size_t nbPairs);
   };


   /**
    * Bracket expressions
    * http://community.topcoder.com/stat?c=problem_statement&pm=13243
    */
   struct BracketExpressions
   {
      static bool isPossible(std::string const&);
   };


   /**
    * Taro string
    * http://community.topcoder.com/stat?c=problem_statement&pm=13006
    */
   struct TaroString
   {
      static bool getAnswer(std::string const&);
   };

   /**
    * WolfDelaymaster
    * http://community.topcoder.com/stat?c=problem_statement&pm=12778
    */
   struct WolfDelaymaster
   {
      static bool isValid(std::string const&);
   };
}
