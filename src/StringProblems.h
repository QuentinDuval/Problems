#pragma once

#include <array>
#include <string>
#include <unordered_set>
#include <utility>
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


   /**  */
   struct SubStringSearch
   {
      static std::string::size_type boyerMooreSearch(std::string const& text, std::string const& pattern);
      static std::string::size_type kmpSearch(std::string const& text, std::string const& pattern);
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

   /**
    * IPv444
    * http://community.topcoder.com/stat?c=problem_statement&pm=11378
    */
   struct IPv444
   {
      using Addr = std::array<int, 4>;
      using AddrPrice = std::pair<Addr, int>;

      static Addr parseAddress(std::string const& request);
      static long long maxAmount(std::vector<std::string> const& requests, std::vector<int> const& prices);
   };

   /**
    * AB
    * http://community.topcoder.com/stat?c=problem_statement&pm=13642
    */
   struct AB
   {
      static std::string createString(size_t size, size_t nbPairs);
   };

   /**
   * ABC
   * http://community.topcoder.com/stat?c=problem_statement&pm=13645
   */
   struct ABC
   {
      static std::string createString(size_t size, size_t nbPairs);
   };

   /**
    * Decipherability
    * http://community.topcoder.com/stat?c=problem_statement&pm=13656
    */
   struct Decipherability
   {
      static bool check(std::string const&, int K);
   };

   /**
    * TaroFillingAStringDiv1
    * http://community.topcoder.com/stat?c=problem_statement&pm=13669
    */
   struct TaroFillingAStringDiv1
   {
      static const int MOD = 1000000007;
      static int getNumber(int n, std::vector<int> const& positions, std::string const& values);
   };

   /**
    * InternetSecurity
    * http://community.topcoder.com/stat?c=problem_statement&pm=11064
    */
   struct InternetSecurity
   {
      using Addresses = std::vector<std::string>;
      using Keywords = std::vector<std::string>;
      static Addresses determineWebsite(Addresses const& addresses, Keywords const& keywords, Keywords const& dangerous, int threshold);
   };

   /**
    * KingSort
    * http://community.topcoder.com/stat?c=problem_statement&pm=11740
    */
   struct KingSort
   {
      using KingNames = std::vector<std::string>;
      static KingNames getSortedList(KingNames const&);
   };

   /**
    * BusAwaiting
    * http://community.topcoder.com/stat?c=problem_statement&pm=8608
    */
   struct BusAwaiting
   {
      static int waitingTime(std::vector<std::string> const& buses, int arrivalTime);
   };

   /**
    * SearchDisks
    * http://community.topcoder.com/stat?c=problem_statement&pm=7525
    */
   struct SearchDisks
   {
      static int numberToTakeOut(std::string const& diskNames, std::string const& searchingDisk);
   };

   /**
    * TemplateMatching
    * http://community.topcoder.com/stat?c=problem_statement&pm=9943
    */
   struct TemplateMatching
   {
      static std::string bestMatch(std::string const& text, std::string const& prefix, std::string const& suffix);
   };

   /**
    * SortBooks
    * http://community.topcoder.com/stat?c=problem_statement&pm=4557
    */
   struct SortBooks
   {
      static std::vector<size_t> checkManually(std::vector<std::string> const& firstFields, std::vector<std::string> const& secondFields);
      static bool qualifyAsTitle(std::string const& field);
      static std::vector<std::string> splitWords(std::string const& s);
   };

   /**
    * SerialNumbers
    * http://community.topcoder.com/stat?c=problem_statement&pm=8171
    */
   struct SerialNumbers
   {
      static std::vector<std::string> sortSerials(std::vector<std::string> const& serialNbs);
   };


   /**
    * TournamentsAmbiguityNumber
    * http://community.topcoder.com/stat?c=problem_statement&pm=7600
    */
   struct TournamentsAmbiguityNumber
   {
      static int scrutinizeTable(std::vector<std::string> const& table);
   };

   /**
    * JoshString
    * http://community.topcoder.com/stat?c=problem_statement&pm=8094
    */
   struct JoshString
   {
      static bool isJoshString(std::string const& str);
   };

   /**
   * QuoteContest
   * http://community.topcoder.com/stat?c=problem_statement&pm=7594
   */
   struct QuoteContest
   {
      static std::string bestQuote(std::vector<std::string> const& quotes);
   };

   /**
   * DownloadingFiles
   * http://community.topcoder.com/stat?c=problem_statement&pm=8400
   */
   struct DownloadingFiles
   {
      static double actualTime(std::vector<std::string> const& taskStrings);
   };

   /**
    * Unique
    * http://community.topcoder.com/stat?c=problem_statement&pm=13067
    */
   struct Unique
   {
      static std::string removeDuplicates(std::string const& str);
   };

   /**
    * TheLargestString
    * http://community.topcoder.com/stat?c=problem_statement&pm=12494
    */
   struct TheLargestString
   {
      static std::string find(std::string const& s, std::string const& t);
   };

   /**
    * LargestSubsequence
    * http://community.topcoder.com/stat?c=problem_statement&pm=11471
    */
   struct LargestSubsequence
   {
      static std::string getLargest(std::string const& str);
   };


   /**
    * EllysSortingTrimmer
    * http://community.topcoder.com/stat?c=problem_statement&pm=12971
    */
   struct EllysSortingTrimmer
   {
      static std::string getMin(std::string const& input, int len);
   };

   /**
    * TheBestName
    * http://community.topcoder.com/stat?c=problem_statement&pm=8413
    */
   struct TheBestName
   {
      static std::vector<std::string> sort(std::vector<std::string> const&);
   };
}
