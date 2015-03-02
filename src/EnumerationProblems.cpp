#include "EnumerationProblems.h"

#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <set>
#include <sstream>



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
}
