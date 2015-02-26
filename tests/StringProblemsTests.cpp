#include "StringProblemsTests.h"
#include "StringProblems.h"
#include "utils/Algorithms.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void StringProblemsTests::allTests()
   {
      testWordSplit();
      doubleLetterTests();
      parenthesesCombinationNbTests();
      bracketExpressionsTests();
      taroStringTests();
      wolfDelaymasterTests();
      ipv444Tests();
      abTests();
      abcTests();
      decipherabilityTests();
      taroFillingAStringDiv1Tests();
      internetSecurityTests();
      busAwaitingTests();
      searchDisksTests();
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::testWordSplit()
   {
      WordSplit::Dict dict = { "split", "into", "in", "to", "words" };
      WordSplit split(dict);

      assert(true == split.splitInWords("splitintoword").empty());
      assert(4 == split.splitInWords("splitintowords").size());
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::doubleLetterTests()
   {
      assert(true == doubleLetter("aabccb"));
      assert(false == doubleLetter("aabccbb"));
      assert(true == doubleLetter("abcddcba"));
      assert(false == doubleLetter("abab"));
      assert(true == doubleLetter("aaaaaaaaaa"));
      assert(false == doubleLetter("aababbabbaba"));
      assert(true == doubleLetter("zzxzxxzxxzzx"));
   }

   //--------------------------------------------------------------------------
   
   void StringProblemsTests::parenthesesCombinationNbTests()
   {
      assert(0 == Parentheses::combinationNb(0).size());
      assert(1 == Parentheses::combinationNb(1).size());
      assert(2 == Parentheses::combinationNb(2).size());
      assert(4 == Parentheses::combinationNb(3).size());

      std::vector<std::string> toShow;
      auto result = Parentheses::combinationNb(4);
      intersperse(result, std::back_inserter(toShow), ", ");
      std::cout << sum(toShow, std::string("")) << std::endl;
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::bracketExpressionsTests()
   {
      assert(true == BracketExpressions::isPossible(""));
      assert(true == BracketExpressions::isPossible("([]{})"));
      assert(true == BracketExpressions::isPossible("(())[]"));
      assert(true == BracketExpressions::isPossible("({X)"));
      assert(false == BracketExpressions::isPossible("({])"));
      assert(false == BracketExpressions::isPossible("[]X"));
      assert(true == BracketExpressions::isPossible("([]X()[()]XX}[])X{{}}]"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::taroStringTests()
   {
      assert(true == TaroString::getAnswer("XCYAZTX"));
      assert(false == TaroString::getAnswer("CTA"));
      assert(false == TaroString::getAnswer("ACBBAT"));
      assert(true == TaroString::getAnswer("SGHDJHFIOPUFUHCHIOJBHAUINUIT"));
      assert(false == TaroString::getAnswer("CCCATT"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::wolfDelaymasterTests()
   {
      assert(true == WolfDelaymaster::isValid("wolf"));
      assert(false == WolfDelaymaster::isValid("wwolfolf"));
      assert(true == WolfDelaymaster::isValid("wolfwwoollffwwwooolllfffwwwwoooollllffff"));
      assert(false == WolfDelaymaster::isValid("flowolf"));
   }

   //--------------------------------------------------------------------------

   static void ipv444ParsingTests()
   {
      IPv444::Addr addr = IPv444::parseAddress("123.25.7.986");
      assert(123 == addr[0]);
      assert(25 == addr[1]);
      assert(7 == addr[2]);
      assert(986 == addr[3]);

      addr = IPv444::parseAddress("0.1.*.*");
      assert(0 == addr[0]);
      assert(1 == addr[1]);
      assert(-1 == addr[2]);
      assert(-1 == addr[3]);
   }

   void StringProblemsTests::ipv444Tests()
   {
      ipv444ParsingTests();
      assert(47 == IPv444::maxAmount({ "66.37.210.86" }, { 47 }));
      assert(1010 == IPv444::maxAmount({ "0.0.0.*", "0.0.0.3", "0.0.0.5" }, { 1, 3, 9 }));

      assert(1000005000006 == IPv444::maxAmount(
         { "*.*.*.*", "123.456.789.0", "434.434.434.434", "999.*.999.*" },
         { 1, 5, 3, 6 }));

      assert(26075718 == IPv444::maxAmount(
         { "*.*.999.999", "888.888.999.*", "888.888.*.999", "777.777.777.777", "777.*.*.777" },
         { 19, 33, 42, 777, 7 }));

      assert(1361957076132 == IPv444::maxAmount(
         { "127.0.0.1", "*.0.0.*", "*.*.255.255", "192.68.*.*" },
         { 999999, 629851, 294016, 438090 }));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::abTests()
   {
      assert("ABB" == AB::createString(3, 2));
      assert("BA" == AB::createString(2, 0));
      assert("" == AB::createString(5, 8));
      assert("ABBBBABBBB" == AB::createString(10, 12));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::abcTests()
   {
      assert("ABC" == ABC::createString(3, 3));
      assert("AAA" == ABC::createString(3, 0));
      assert("" == ABC::createString(5, 10));
      assert("AAAAAAAAAAAABBB" == ABC::createString(15, 36));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::decipherabilityTests()
   {
      assert(true == Decipherability::check("snuke", 2));
      assert(true == Decipherability::check("aba", 1));
      assert(false == Decipherability::check("aba", 2));
      assert(true == Decipherability::check("abcdabcd", 3));
      assert(false == Decipherability::check("koukyoukoukokukikou", 2));
      assert(false == Decipherability::check("wolfsothe", 8));
      assert(true == Decipherability::check("aa", 2));
   }
   
   //--------------------------------------------------------------------------

   void StringProblemsTests::taroFillingAStringDiv1Tests()
   {
      assert(2 == TaroFillingAStringDiv1::getNumber(3, { 1, 3 }, "AB"));
      assert(1 == TaroFillingAStringDiv1::getNumber(4, { 2, 1, 3, 4 }, "ABBA"));
      assert(1 == TaroFillingAStringDiv1::getNumber(25, { 23, 4, 8, 1, 24, 9, 16, 17, 6, 2, 25, 15, 14, 7, 13 }, "ABBBBABABBAAABA"));
      assert(43068480 == TaroFillingAStringDiv1::getNumber(305,
         {183, 115, 250, 1, 188, 193, 163, 221, 144, 191, 92, 192, 58, 215, 157, 187, 227, 177, 206, 15, 272, 232, 49, 11, 178, 59, 189, 246},
         "ABAABBABBAABABBBBAAAABBABBBA"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::internetSecurityTests()
   {
      auto res = InternetSecurity::determineWebsite(
      { "www.topcoder.com", "www.sindicate_of_evil.com", "www.happy_citizens.com" },
      { "hack encryption decryption internet algorithm", "signal interference evil snake poison algorithm", "flower baloon topcoder blue sky sea" },
      {"hack", "encryption", "decryption", "interference", "signal", "internet"}, 3);
      assert(equal(InternetSecurity::Addresses{ "www.topcoder.com", "www.sindicate_of_evil.com" }, res));

      res = InternetSecurity::determineWebsite(
      { "brokenlink", "flowerpower.net", "purchasedomain.com" },
      {"broken", "rose tulips", "cheap free domain biggest greatest"},
      {"biggest", "enemy", "hideout"},
      2);
      assert(0 == res.size());

      res = InternetSecurity::determineWebsite(
      { "a..a.ab.", "...aa.b" },
      { "a bc def", "def ghij klmno" },
      { "a", "b", "c", "d", "e" },
      1);
      assert(equal(InternetSecurity::Addresses{ "a..a.ab.", "...aa.b" }, res));

      res = InternetSecurity::determineWebsite(
      { "www.tsa.gov" },
      { "information assurance signal intelligence research" },
      { "signal", "assurance", "penguin" },
      2);
      assert(equal(InternetSecurity::Addresses{ "www.tsa.gov" }, res));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::kingSortTests()
   {
      auto res = KingSort::getSortedList({ "Louis IX", "Louis VIII" });
      assert(equal(KingSort::KingNames{ "Louis VIII", "Louis IX" }, res));

      res = KingSort::getSortedList({ "Louis IX", "Philippe II" });
      assert(equal(KingSort::KingNames{ "Louis IX", "Philippe II" }, res));

      res = KingSort::getSortedList({ "Richard III", "Richard I", "Richard II" });
      assert(equal(KingSort::KingNames{ "Richard I", "Richard II", "Richard III" }, res));

      res = KingSort::getSortedList({ "John X", "John I", "John L", "John V" });
      assert(equal(KingSort::KingNames{ "John I", "John V", "John X", "John L" }, res));

      res = KingSort::getSortedList({ "Philippe VI", "Jean II", "Charles V", "Charles VI", "Charles VII", "Louis XI" });
      assert(equal(KingSort::KingNames{ "Charles V", "Charles VI", "Charles VII", "Jean II", "Louis XI", "Philippe VI" }, res));

      res = KingSort::getSortedList({ "Philippe II", "Philip II" });
      assert(equal(KingSort::KingNames{ "Philippe II", "Philip II" }, res));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::busAwaitingTests()
   {
      assert(15 == BusAwaiting::waitingTime({ "150 50 10" }, 285));
      assert(0 == BusAwaiting::waitingTime({ "123456 10000 1" }, 123456));
      
      assert(121163 == BusAwaiting::waitingTime(
         { "270758 196 67",
         "904526 8930 66",
         "121164 3160 56" },1 ));

      assert(-1 == BusAwaiting::waitingTime(
         { "718571 2557 74",
         "480573 9706 54",
         "16511 6660 90" }, 1000000));

      assert(1776 == BusAwaiting::waitingTime(
         { "407917 8774 24",
         "331425 4386 58",
         "502205 9420 32",
         "591461 1548 79",
         "504695 8047 53" }, 395439));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::searchDisksTests()
   {
      assert(0 == SearchDisks::numberToTakeOut("beatles queen abba", "abba"));
      assert(2 == SearchDisks::numberToTakeOut("beatles queen abba", "beatles"));
      assert(1 == SearchDisks::numberToTakeOut("a b c", "b"));
      assert(11 == SearchDisks::numberToTakeOut("t k o h z s v r i c e d n f a m u w p g j q x y l", "f"));
   }
}
