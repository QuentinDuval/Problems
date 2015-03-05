#pragma once


namespace prob
{
   /**
   * TheNumberGame
   * http://community.topcoder.com/stat?c=problem_statement&pm=12474
   */
   struct TheNumberGame
   {
      static bool manaoWin(int manaoNb, int oponentNb);
   };

   /**
    * http://community.topcoder.com/stat?c=problem_statement&pm=13239
    */
   struct FixedDiceGameDiv1
   {
      static double getExpectation(int aliceRolls, int aliceSides, int bobRolls, int bobSides);
   };
}
