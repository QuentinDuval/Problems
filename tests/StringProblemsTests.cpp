#include "StringProblemsTests.h"
#include "StringProblems.h"
#include "utils/Algorithms.h"
#include "utils/Numeric.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   void StringProblemsTests::allTests()
   {
      testWordSplit();
      subStringSearchTests();
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
      templateMatchingTests();
      sortBooksTests();
      serialNumbersTests();
      tournamentsAmbiguityNumberTests();
      joshStringTests();
      quoteContestTests();
      downloadingFilesTests();
      uniqueTests();
      theLargestStringTests();
      largestSubsequenceTests();
      ellysSortingTrimmerTests();
      theBestNameTests();
      stringFragmentationTests();
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

   template<typename Algo>
   void subStringSearchTest(Algo algo)
   {
      assert(std::string::npos == algo("", "sub-string"));
      assert(std::string::npos == algo("substring search into words", ""));
      assert(std::string::npos == algo("substring search into words", "sub-string"));

      assert(0 == algo("substring search into words", "substring"));
      assert(10 == algo("substring search into words", "search"));
   }

   void StringProblemsTests::subStringSearchTests()
   {
      subStringSearchTest(SubStringSearch::boyerMooreSearch);
      subStringSearchTest(SubStringSearch::kmpSearch);
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
      utils::intersperse(result, std::back_inserter(toShow), ", ");
      std::cout << utils::sum(toShow, std::string("")) << std::endl;
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
      assert(utils::equal(InternetSecurity::Addresses{ "www.topcoder.com", "www.sindicate_of_evil.com" }, res));

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
      assert(utils::equal(InternetSecurity::Addresses{ "a..a.ab.", "...aa.b" }, res));

      res = InternetSecurity::determineWebsite(
      { "www.tsa.gov" },
      { "information assurance signal intelligence research" },
      { "signal", "assurance", "penguin" },
      2);
      assert(utils::equal(InternetSecurity::Addresses{ "www.tsa.gov" }, res));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::kingSortTests()
   {
      auto res = KingSort::getSortedList({ "Louis IX", "Louis VIII" });
      assert(utils::equal(KingSort::KingNames{ "Louis VIII", "Louis IX" }, res));

      res = KingSort::getSortedList({ "Louis IX", "Philippe II" });
      assert(utils::equal(KingSort::KingNames{ "Louis IX", "Philippe II" }, res));

      res = KingSort::getSortedList({ "Richard III", "Richard I", "Richard II" });
      assert(utils::equal(KingSort::KingNames{ "Richard I", "Richard II", "Richard III" }, res));

      res = KingSort::getSortedList({ "John X", "John I", "John L", "John V" });
      assert(utils::equal(KingSort::KingNames{ "John I", "John V", "John X", "John L" }, res));

      res = KingSort::getSortedList({ "Philippe VI", "Jean II", "Charles V", "Charles VI", "Charles VII", "Louis XI" });
      assert(utils::equal(KingSort::KingNames{ "Charles V", "Charles VI", "Charles VII", "Jean II", "Louis XI", "Philippe VI" }, res));

      res = KingSort::getSortedList({ "Philippe II", "Philip II" });
      assert(utils::equal(KingSort::KingNames{ "Philippe II", "Philip II" }, res));
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

   //--------------------------------------------------------------------------

   void StringProblemsTests::templateMatchingTests()
   {
      assert("something" == TemplateMatching::bestMatch("something", "awesome", "ingenious"));
      assert("a" == TemplateMatching::bestMatch("havka", "eto", "papstvo"));
      assert("abrac" == TemplateMatching::bestMatch("abracadabra", "habrahabr", "bracket"));
      assert("ippi" == TemplateMatching::bestMatch("mississippi", "promise", "piccolo"));
      assert("a a" == TemplateMatching::bestMatch("a a a a a a", "a a", "a"));
      assert("b" == TemplateMatching::bestMatch("ab", "b", "a"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::sortBooksTests()
   {
      auto res = SortBooks::checkManually(
         { "J R R Tolkien", "THE Jungle BOOK" },
         { "THE HOBBIT", "RUDYARD KIPLING" });
      assert(utils::equal(std::vector<size_t>{ 0 }, res));

      res = SortBooks::checkManually(
      { "Scaramouche", "Dan Brown", "War and Peace" },
      { "Rafael Sabatini", "The Da Vinci Code", "Leo Tolstoy" });
      assert(utils::equal(std::vector<size_t>{ 0 }, res));

      res = SortBooks::checkManually(
         { "Lost     Horizon" },
         { "James Hilton" });
      assert(utils::equal(std::vector<size_t>{ 0 }, res));

      res = SortBooks::checkManually(
      { "andy rooney", "joe lofthouse", "Theodore Taylor" },
      { "love of life", "the arrest", "Softly Wandering" });
      assert(utils::equal(std::vector<size_t>{ 2 }, res));

      res = SortBooks::checkManually(
      { "Aesop", "Little Women", "Hans Christian Anderson", "The Arabian Nights",
      "Peter Christian Asbornsen", "Mr Poppers Penguins", "Enid Bagnold", "Miss Hickory",
      "Sir James Barrie", "The Wizard of OZ", "Ludwig Bemelmans", "The Five Chinese Brothers",
      "Edith Nesbit Bland", "The Enchanted Castle", "Edith Nesbit Bland",
      "Five Children and It", "Michael Bond", "The Children of Green Knowe",
      "James Boyd", "Caddie Woodlawn", "Walter Brooks", "The Runaway Bunny",
      "Margaret Wise Brown", "Big Red Barn", "Jean De Brunhoff",
      "Old Mother West Wind", "Frances Hodgson Burnett", "A Little Princess",
      "Frances Hodgson Burnett", "Mike Mulligan and His Steam Shovel",
      "Virginia Lee Burton", "The Enormous Egg", "Eleanor Cameron",
      "The Happy Orpheline", "Natalie Savage Carlson", "Through the Looking Glass",
      "Miguel Cervantes", "Secret of the Andes", "Beverly Cleary", "Henry Huggins",
      "Elizabeth Coatsworth", "The Adventures of Pinocchio", "Barbara Cooney",
      "The Little Lame Prince", "Paul Creswick", "The Courage of Sarah Noble",
      "Alice Dagliesh" },
      { "Aesops Fables", "Louisa May Alcott", "Fairy Tales", "Hans Christian Anderson",
      "East of the Sun and West of the Moon", "Richard and Florence Atwater",
      "National Velvet", "Carolyn Bailey", "Peter Pan", "Frank L Baum", "Madeline",
      "Claire Huchet Bishop", "The Railway Children", "Edith Nesbit Bland",
      "The Story of the Treasure Seekers", "Edith Nesbit Bland", "A Bear Called Paddington",
      "Lucy Boston", "Drums", "Carol Rylie Brink", "Freddy the Detective",
      "Margaret Wise Brown", "The Little Fur Family", "Moon Goodnight", "The Story of Babar",
      "Thornton W Burgess", "Little Lord Fauntleroy", "Frances Hodgson Burnett",
      "The Secret Garden", "Virginia Lee Burton", "The Little House", "Oliver Butterworth",
      "The Wonderful Flight to the Mushroom Planet", "Natalie Savage Carlson",
      "The Family Under the Bridge", "Lewis Carroll", "Don Quixote", "Ann Nolan Clark",
      "Beezus and Ramona", "Beverly Cleary", "The Cat Who Went to Heaven", "Carlo Collodi",
      "Chanticleer and the Fox", "Dinah Mulock Craik", "Robin Hood", "Alice Dagliesh",
      "The Bears on Hemlock Mountain" });
      assert(utils::equal(std::vector<size_t>{0, 1, 2, 6, 7, 8, 10, 18, 19, 23, 26, 27, 36, 39, 44 }, res));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::serialNumbersTests()
   {
      auto res = SerialNumbers::sortSerials({ "ABCD", "145C", "A", "A910", "Z321" });
      assert(utils::equal(std::vector<std::string>{"A", "ABCD", "Z321", "145C", "A910" }, res));

      res = SerialNumbers::sortSerials({ "Z19", "Z20" });
      assert(utils::equal(std::vector<std::string>{ "Z20", "Z19" }, res));

      res = SerialNumbers::sortSerials({ "34H2BJS6N", "PIM12MD7RCOLWW09", "PYF1J14TF", "FIPJOTEA5" });
      assert(utils::equal(std::vector<std::string>{"FIPJOTEA5", "PYF1J14TF", "34H2BJS6N", "PIM12MD7RCOLWW09" }, res));

      res = SerialNumbers::sortSerials({ "ABCDE", "BCDEF", "ABCDA", "BAAAA", "ACAAA" });
      assert(utils::equal(std::vector<std::string>{"ABCDA", "ABCDE", "ACAAA", "BAAAA", "BCDEF" }, res));
   }

   //--------------------------------------------------------------------------
   
   void StringProblemsTests::tournamentsAmbiguityNumberTests()
   {
      assert(3 == TournamentsAmbiguityNumber::scrutinizeTable({ "-10", "0-1", "10-" }));
      assert(0 == TournamentsAmbiguityNumber::scrutinizeTable({ "-1", "0-" }));

      assert(0 == TournamentsAmbiguityNumber::scrutinizeTable
      ({ "----",
         "----",
         "----",
         "----" }));

      assert(198 == TournamentsAmbiguityNumber::scrutinizeTable
      ({ "--1-10-1---1--1-00",
         "--0110000--0---10-",
         "01--00000100-00011",
         "-0---0010-11110100",
         "001--01-00-0001-1-",
         "11111--100--1-1-01",
         "-1110--00110-11-01",
         "0110-01--100110-10",
         "-111111---01--0-01",
         "--0-1100----10011-",
         "--10--011--1--101-",
         "01101-110-0--1-0-1",
         "---010-0-0---00-11",
         "--101-00-1-01-0-0-",
         "0-110001110-11-110",
         "-010-----011--0--0",
         "11010110100-010--0",
         "1-01-0010--00-111-" }));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::joshStringTests()
   {
      assert(true == JoshString::isJoshString("bad"));
      assert(false == JoshString::isJoshString("badbad"));
      assert(false == JoshString::isJoshString("abcdefghijklmnopqrstuvwxyz"));
      assert(true == JoshString::isJoshString("abcdefghijklmnopqrstuvwxyzaa"));
      assert(true == JoshString::isJoshString("asdjkhqwaieyajhdjsahjquawyhasdhwauyashjzxdf"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::quoteContestTests()
   {
      assert("secondquote" == QuoteContest::bestQuote({ "4 1 firstquote", "10 2 secondquote", "1 5 thirdquote" }));
      assert("nocodecanbreakme" == QuoteContest::bestQuote({ "13 5 nocodecanbreakme", "10 6 iamthebest", "13 2 trytochallengeme" }));
      assert("aboutthechallenge" == QuoteContest::bestQuote({ "1 1 justdoit", "1 2 thewinnertakeitall", "1 4 aboutthechallenge" }));
      assert("theworstquoteintheworld" == QuoteContest::bestQuote({ "1 1 theworstquoteintheworld" }));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::downloadingFilesTests()
   {
      assert(43.0 == DownloadingFiles::actualTime({ "3 57", "2 22" }));
      assert(1043.0 == DownloadingFiles::actualTime({ "3 1057", "2 1022" }));
      assert(2500.0 == DownloadingFiles::actualTime({ "25 1000", "5 5000", "10 5000" }));
      assert(27.5 == DownloadingFiles::actualTime({ "1 10", "1 20", "2 40" }));
      assert(equalWithDelta(4414.542662116041,
         DownloadingFiles::actualTime({ "6 88", "39 7057", "63 2502", "45 2285", "28 8749", "62 3636", "1 5546", "49 5741" })
         , 1e-6));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::uniqueTests()
   {
      assert("ban" == Unique::removeDuplicates("banana"));
      assert("ardvk" == Unique::removeDuplicates("aardvark"));
      assert("x" == Unique::removeDuplicates("xxxxx"));
      assert("topcder" == Unique::removeDuplicates("topcoder"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::theLargestStringTests()
   {
      assert("by" == TheLargestString::find("ab", "zy"));
      assert("cbaaaa" == TheLargestString::find("abacaba", "zzzaaaa"));
      assert("xx" == TheLargestString::find("x", "x"));
      assert("bbbbbbbbbbbbbbbbbbaaab" == TheLargestString::find("abbabbabbababaaaabbababab", "bababbaabbbababbbbababaab"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::largestSubsequenceTests()
   {
      assert("tt" == LargestSubsequence::getLargest("test"));
      assert("a" == LargestSubsequence::getLargest("a"));
      assert("xple" == LargestSubsequence::getLargest("example"));
      assert("zyog" == LargestSubsequence::getLargest("aquickbrownfoxjumpsoverthelazydog"));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::ellysSortingTrimmerTests()
   {
      assert("AAAAA" == EllysSortingTrimmer::getMin("ABRACADABRA", 5));
      assert("EIP" == EllysSortingTrimmer::getMin("ESPRIT", 3));
      assert("AABGINZ" == EllysSortingTrimmer::getMin("BAZINGA", 7));
      assert("ABCDEFGHIJKLM" == EllysSortingTrimmer::getMin("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 13));
      assert("ABCDEFGHIJKLM" == EllysSortingTrimmer::getMin("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 13));
      assert("AAAAAAAAABBDDDDDDDEEI" == EllysSortingTrimmer::getMin("AAAWDIUAOIWDESBEAIWODJAWDBPOAWDUISAWDOOPAWD", 21));
      assert("CDT" == EllysSortingTrimmer::getMin("TOPCODER", 3));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::theBestNameTests()
   {
      auto res = TheBestName::sort({ "JOHN", "PETR", "ACRUSH" });
      assert(utils::equal(std::vector<std::string>({ "JOHN", "ACRUSH", "PETR" }), res));

      res = TheBestName::sort({ "GLUK", "MARGARITKA" });
      assert(utils::equal(std::vector<std::string>({ "MARGARITKA", "GLUK" }), res));

      res = TheBestName::sort({ "JOHN", "A", "AA", "AAA", "JOHN", "B", "BB", "BBB", "JOHN", "C", "CC", "CCC", "JOHN" });
      assert(utils::equal(std::vector<std::string>({ "JOHN", "JOHN", "JOHN", "JOHN", "CCC", "BBB", "CC", "BB", "AAA", "C", "AA", "B", "A" }), res));

      res = TheBestName::sort({ "BATMAN", "SUPERMAN", "SPIDERMAN", "TERMINATOR" });
      assert(utils::equal(std::vector<std::string>({ "TERMINATOR", "SUPERMAN", "SPIDERMAN", "BATMAN" }), res));
   }

   //--------------------------------------------------------------------------

   void StringProblemsTests::stringFragmentationTests()
   {
      assert(9 ==    StringFragmentation::largestFontSize("ONE TWO THREE FOUR FIVE", 150, 40));
      assert(10 ==   StringFragmentation::largestFontSize("ONE TWO THREE FOUR FIVE", 150, 60));
      assert(28 ==   StringFragmentation::largestFontSize("ONE TWO THREE FOUR FIVE", 150, 10000));
      assert(1250 == StringFragmentation::largestFontSize("ONE TWO THREE FOUR FIVE", 10000, 10000));
      assert(-1 ==   StringFragmentation::largestFontSize("ONE TWO THREE FOUR FIVE", 50, 50));
      assert(-1 ==   StringFragmentation::largestFontSize("A", 9, 14));
   }
}
