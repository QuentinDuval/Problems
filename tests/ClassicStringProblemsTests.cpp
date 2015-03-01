#include "ClassicStringProblemsTests.h"
#include "ClassicStringProblems.h"

#include <assert.h>
#include <iostream>
#include <vector>


namespace prob
{
   void ClassicStringProblemsTests::allTests()
   {
      firstNonRepeatedCharTests();
      removeCharsTests();
      reverseWordsTests();
      permutationsTests();
      combinationsTests();
      phoneWordsTests();
   }

   //--------------------------------------------------------------------------

   void ClassicStringProblemsTests::firstNonRepeatedCharTests()
   {
      assert(false == firstNonRepeatedChar("").first);
      assert(std::make_pair(true, 'd') == firstNonRepeatedChar("abcdcba"));
      assert(std::make_pair(true, 'e') == firstNonRepeatedChar("abcedcba"));
      assert(false == firstNonRepeatedChar("abccba").first);
   }

   //--------------------------------------------------------------------------

   void ClassicStringProblemsTests::removeCharsTests()
   {
      std::string s("harbor");
      removeCharsManual(s, "aeiouy");
      assert("hrbr" == s);
   }

   //--------------------------------------------------------------------------

   void ClassicStringProblemsTests::reverseWordsTests()
   {
      std::string s("Let us reverse this sentence nicely.");
      reverseWords(s);
      assert("nicely. sentence this reverse us Let" == s);
   }

   //--------------------------------------------------------------------------

   void ClassicStringProblemsTests::permutationsTests()
   {
      auto res = permutations("abc");
      assert(6 == res.size());
      for (auto& s : res)
         std::cout << s << std::endl;
   }

   void ClassicStringProblemsTests::combinationsTests()
   {
      auto res = combinations("abc");
      assert(7 == res.size());
      for (auto& s : res)
         std::cout << s << std::endl;
   }

   //--------------------------------------------------------------------------

   void ClassicStringProblemsTests::phoneWordsTests()
   {
      std::string phoneNb("866-2665");
      auto res = phoneWords(phoneNb);
      assert(end(res) != std::find(begin(res), end(res), "TOO-COOL"));
   }
}
