#pragma once

#include <vector>


namespace prob
{
   /** CtuRobots - http://community.topcoder.com/stat?c=problem_statement&pm=13595 */


   /**
    * JumpFurther
    * http://community.topcoder.com/stat?c=problem_statement&pm=12300
    */
   struct JumpFurther
   {
      static int furthest(int N, int badStep);
   };


   /**
    * TheConsecutiveIntegersDivOne
    * http://community.topcoder.com/stat?c=problem_statement&pm=13625
    */
   struct TheConsecutiveIntegersDivOne
   {
      static int find(std::vector<int> const& numbers, int k);
   };
}
