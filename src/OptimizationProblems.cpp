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


   //--------------------------------------------------------------------------
   // TheConsecutiveIntegersDivOne:
   // - The order does not matter => sorting
   // - Then find the set [i..i+k-1] with the minimum difference between them
   // - The result is then:
   //   (dist[i, i+1] - 1) + 2 * (dist[i+1, i+2] - 1) + ...
   //                      + 2 * (dist[i+k-3, i+k-2] - 1) + (dist[i+k-2, i+k-1] - 1)
   //--------------------------------------------------------------------------

   int TheConsecutiveIntegersDivOne::find(std::vector<int> const& numbers, int k)
   {
      if (k < 2)
         return 0;

      std::vector<int> sortedNbs(numbers);
      std::sort(begin(sortedNbs), end(sortedNbs));

      int minDist = std::numeric_limits<int>::max();
      for (size_t start = 0; start < sortedNbs.size() - k; ++start)
      {
         int dist = 0;
         for (size_t j = start + 1; j < start + k; ++j)
         {
            int added = sortedNbs[j] - sortedNbs[j - 1] - 1;
            dist += added * std::min(j - start, start + k - j);
         }
         minDist = std::min(minDist, dist);
      }

      return minDist;
   }


   //--------------------------------------------------------------------------
   // JanuszTheBusinessman
   // Several promotion attribution policies:
   //
   // 1. Give the promotion to the ones intersection the most
   // Issues with the case of 5 clients intersecting prev and next. How to decide?
   //
   // 2. Give the promotion to the ones staying the longest. Same issue.
   //
   // 3. Analyze the clients in order or arrival. 
   // For each non-satisfied customer, find all intersecting customers.
   // And give a promotion to the one intersecting the most.
   // Mark the colliding and repeat.
   //
   //--------------------------------------------------------------------------

   using Duration = std::pair<int, int>;

   static std::vector<size_t> collidingWith(
      std::vector<Duration> const& durations,
      std::vector<bool> const& satisfied,
      size_t client)
   {
      std::vector<size_t> colliding;
      for (size_t c = 0; c < durations.size(); ++c)
      {
         if (satisfied[c])
            continue;

         if (std::max(durations[c].first, durations[client].first)
            <= std::min(durations[c].second, durations[client].second))
            colliding.push_back(c);
      }
      return colliding;
   }

   int JanuszTheBusinessman::minPromotions(std::vector<int> const& arrivals, std::vector<int> const& departures)
   {
      std::vector<Duration> durations(arrivals.size());
      zipWith(arrivals, departures, begin(durations), MakePair());
      sortBy(durations, comparingWith(GetFirst()));

      int promotionCount = 0;
      std::vector<bool> satisfied(durations.size(), false);

      for (size_t client = 0; client < durations.size(); ++client)
      {
         if (satisfied[client])
            continue;

         std::vector<size_t> maxCollisions = collidingWith(durations, satisfied, client);

         for (size_t next = 1; next < durations.size(); ++next)
         {
            if (durations[next].first > durations[client].second)
               break;

            std::vector<size_t> collisions = collidingWith(durations, satisfied, next);
            if (collisions.size() > maxCollisions.size())
               std::swap(collisions, maxCollisions);
         }

         ++promotionCount;
         for (size_t i : maxCollisions)
            satisfied[i] = true;
      }

      return promotionCount;
   }
}
