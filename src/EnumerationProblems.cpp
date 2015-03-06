#include "EnumerationProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <map>
#include <set>
#include <sstream>
#include <unordered_map>


namespace prob
{
   static int reversedNb(int n)
   {
      std::ostringstream stream;
      stream << n;
      std::string repr = stream.str();
      std::reverse(begin(repr), end(repr));
      return atoi(repr.c_str());
   }

   static void fillReachable(int n, std::set<int>& reachable)
   {
      int rev = reversedNb(n);
      reachable.insert(n);
      reachable.insert(rev);
      if (n > 0)
      {
         fillReachable(n / 10, reachable);
         fillReachable(rev / 10, reachable);
      }
   }

   bool TheNumberGame::manaoWin(int manao, int opponent)
   {
      std::set<int> manaoNbs;
      std::set<int> opponentNbs;
      fillReachable(manao, manaoNbs);
      fillReachable(opponent, opponentNbs);

      std::vector<int> resultDiff;
      std::set_difference(
         begin(opponentNbs), end(opponentNbs),
         begin(manaoNbs), end(manaoNbs), std::back_inserter(resultDiff));
      return resultDiff.empty();
   }

   //--------------------------------------------------------------------------

   struct DiceValues
   {
      using Values = std::map<int, long long>;

      /**
      * Return the possible dice values, each values associated with the number of ways we can get it
      * Computation based on divide and conquer (like matrix exponentiation)
      */
      static Values find(int rollCount, int sides)
      {
         if (1 == rollCount)
         {
            Values possibles;
            for (int i = 1; i <= sides; ++i)
               possibles.emplace(i, 1);
            return possibles;
         }
         else if (rollCount % 2)
         {
            auto p1 = find(rollCount - 1, sides);
            auto p2 = find(1, sides);
            return assemble(p1, p2);
         }
         else
         {
            auto ps = find(rollCount / 2, sides);
            return assemble(ps, ps);
         }
      }

      static Values assemble(Values const& lhs, Values const& rhs)
      {
         Values out;
         for (auto& left : lhs)
         for (auto& right : rhs)
            out[left.first + right.first] += left.second * right.second;
         return out;
      }
   };



   double FixedDiceGameDiv1::getExpectation(int aliceRolls, int aliceSides, int bobRolls, int bobSides)
   {
      //Get all alice values, and remove the one that cannot lead to a win
      DiceValues::Values aliceValues = DiceValues::find(aliceRolls, aliceSides);
      auto aliceStart = aliceValues.lower_bound(bobRolls + 1);
      aliceValues.erase(begin(aliceValues), aliceStart);
      if (aliceValues.empty())
         return -1;

      //Get all bobs values, and remove the ones that cannot lead to alice win (too high)
      DiceValues::Values bobValues = DiceValues::find(bobRolls, bobSides);
      int highestAlice = aliceValues.rbegin()->first;
      auto bobEnd = bobValues.lower_bound(highestAlice);
      bobValues.erase(bobEnd, end(bobValues));

      //Count the number of possible ways to have Alice win for each value she can throw
      int totalCombinations = 0;
      std::unordered_map<int, long long> possibleWins;
      for (auto& alice : aliceValues)
      {
         auto bobEnd = bobValues.lower_bound(highestAlice);
         for (auto it = begin(bobValues); it != bobEnd; ++it)
         {
            long long combi = alice.second * it->second;
            possibleWins[alice.first] += combi;
            totalCombinations += combi;
         }
      }

      //Compute the ponderated average and return it
      double average = 0.;
      for (auto& win : possibleWins)
         average += win.first * (win.second * 1.0 / totalCombinations);
      return average;
   }
}
