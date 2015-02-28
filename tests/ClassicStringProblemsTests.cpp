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
}
