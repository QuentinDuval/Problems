#include "OptimizationProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"


namespace prob
{
   int JumpFurther::furthest(int N, int badStep)
   {
      int furthest = 0;
      for (int jump = 1; jump <= N; ++jump)
      {
         furthest += jump;
         if (furthest == badStep)
            furthest -= 1; //do not jump first step
      }
      return furthest;
   }

}
