#include "OptimizationProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"
#include <set>


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
   using Durations = std::vector<Duration>;

   static bool intersect(Durations const& durations, size_t i, size_t j)
   {
      return std::max(durations[i].first, durations[j].first) <= std::min(durations[i].second, durations[j].second);
   }

   static std::vector<size_t> collidingWith(Durations const& durations, std::vector<bool> const& satisfied, size_t client)
   {
      std::vector<size_t> colliding;
      for (size_t c = 0; c < durations.size(); ++c)
      {
         if (!satisfied[c] && intersect(durations, c, client))
            colliding.push_back(c);
      }
      return colliding;
   }

   int JanuszTheBusinessman::minPromotions(std::vector<int> const& arrivals, std::vector<int> const& departures)
   {
      Durations durations(arrivals.size());
      zipWith(arrivals, departures, begin(durations), MakePair());
      sortBy(durations, comparingWith(GetFirst()));

      int promotionCount = 0;
      std::vector<bool> satisfied(durations.size(), false);

      for (size_t client = 0; client < durations.size(); ++client)
      {
         if (satisfied[client])
            continue;

         std::vector<size_t> maxCollisions;
         for (size_t next = 0; next < durations.size(); ++next)
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

   //--------------------------------------------------------------------------
   // BuildingTowersEasy
   //
   // In this problem, each of the restriction carves the search space, removing some possible solutions.
   // The goal is to remove the forbidden spaces, defined by affine functions.
   // The take the maximum of the possible solutions.
   //--------------------------------------------------------------------------

   int BuildingTowersEasy::maxHeight(int n, std::vector<int> const& restrictionIndices, std::vector<int> const& restrictions)
   {
      //Initial restriction due to building 1 being of size 0
      std::vector<int> heights(n);
      for (size_t i = 0; i < heights.size(); ++i)
         heights[i] = i;
      
      //Adding the other restrictions
      for (int building = 0; building < n; ++building)
      {
         for (size_t restriction = 0; restriction < restrictionIndices.size(); ++restriction)
         {
            int target = restrictionIndices[restriction];
            int limit = restrictions[restriction] + abs(building - target + 1);
            heights[building] = std::min(heights[building], limit);
         }
      }

      //Return the highest building of all
      return *std::max_element(begin(heights), end(heights));
   }


   //--------------------------------------------------------------------------
   // BUILDING ROUTES
   //--------------------------------------------------------------------------

   struct BuildingRoutesImpl
   {
      explicit BuildingRoutesImpl(size_t cityCount)
         : m_cityCount(cityCount)
         , m_pathMaxCount(m_cityCount * m_cityCount, 0)
      {}

      size_t m_cityCount;
      std::vector<int> m_pathMaxCount;

      size_t index(size_t x, size_t y)
      {
         return x + y * m_cityCount;
      }

      void incrementAlongPaths(std::vector<std::set<size_t>> const& nextOnPath, size_t i, size_t j)
      {
         if (i == j)
            return;

         //Explore all path and add 1 on the way
         for (size_t next : nextOnPath[index(i, j)])
         {
            if (next == i)
               continue;

            m_pathMaxCount[index(i, next)] += 1;
            incrementAlongPaths(nextOnPath, next, j);
         }
      }

      int build(std::vector<std::string> const& distances, int safeThreshold)
      {
         std::vector<int> shortestPaths(m_cityCount * m_cityCount, 0);
         std::vector<std::set<size_t>> nextOnPath(m_cityCount * m_cityCount);

         //Init the distance matrix
         for (size_t i = 0; i < m_cityCount; ++i)
         for (size_t j = 0; j < m_cityCount; ++j)
         {
            shortestPaths[index(i, j)] = distances[i][j] - '0';
            nextOnPath[index(i, j)].insert(j);
         }

         //Compute the shortest paths and keep track of possible paths (floyd-warshall)
         for (size_t k = 0; k < m_cityCount; ++k)
         {
            for (size_t i = 0; i < m_cityCount; ++i)
            for (size_t j = 0; j < m_cityCount; ++j)
            {
               if (i == j || i == k || k == j)
                  continue;

               int dist = shortestPaths[index(i, k)] + shortestPaths[index(k, j)];
               if (dist < shortestPaths[index(i, j)])
               {
                  shortestPaths[index(i, j)] = dist;
                  nextOnPath[index(i, j)] = nextOnPath[index(i, k)];
               }
               else if (dist == shortestPaths[index(i, j)])
               {
                  for (auto n : nextOnPath[index(i, k)])
                     nextOnPath[index(i, j)].insert(n);
               }
            }
         }

         //Count the number of path that can take each segment
         for (size_t i = 0; i < m_cityCount; ++i)
         for (size_t j = 0; j < m_cityCount; ++j)
         {
            incrementAlongPaths(nextOnPath, i, j);
         }

         //Sum the length of the segments that risk to be used more than threshold times
         int toRebuild = 0;
         for (size_t i = 0; i < m_cityCount; ++i)
         for (size_t j = 0; j < m_cityCount; ++j)
         {
            if (safeThreshold <= m_pathMaxCount[index(i, j)])
               toRebuild += distances[i][j] - '0';
         }
         return toRebuild;
      }
   };

   int BuildingRoutes::build(std::vector<std::string> const& distances, int safeThreshold)
   {
      BuildingRoutesImpl impl(distances.size());
      return impl.build(distances, safeThreshold);
   }


   //--------------------------------------------------------------------------
   // ZOO EXCHANGE PROGRAM
   //--------------------------------------------------------------------------

   static bool isInRange(int val, int lower, int upper)
   {
      return (lower <= val) && (val <= upper);
   }

   int ZooExchangeProgram::minGroup(std::vector<int> const& labels, int lower, int upper)
   {
      //Pre-processing: identifying the groups, take as big as possible
      std::vector<std::set<int>> groups(1);
      for (size_t animal = 0; animal < labels.size(); ++animal)
      {
         int label = labels[animal];
         if (isInRange(label, lower, upper))
            groups.back().insert(label);
         else if (!groups.back().empty())
            groups.emplace_back();
      }

      //Initialization
      std::set<int> searched;
      for (int label = lower; label <= upper; ++label)
         searched.insert(label);

      //Order group by decreasing order
      auto sizeComparison = comparingWith([](std::set<int> const& s) { return s.size(); });

      //Greedy approach
      int count = 0;
      while (!searched.empty())
      {
         eraseIf(groups, [](std::set<int> const& s) { return s.empty(); });
         auto it = maxBy(groups, sizeComparison);
         if (it == end(groups))
            return -1;

         std::vector<int> toRemove(it->begin(), it->end());
         for (auto label : toRemove)
         {
            searched.erase(label);
            for (auto& g : groups)
               g.erase(label);
         }
         ++count;
      }
      return count;
   }

   //--------------------------------------------------------------------------
   // SHOPPING SURVEY
   //--------------------------------------------------------------------------

   int ShoppingSurveyDiv1::minValue(int customers, int bigShopperThreshold, std::vector<int> const& sellCounts)
   {
      std::vector<int> customerCounts(customers, 0);
      auto endBig = begin(customerCounts);
      auto nextLow = begin(customerCounts);
      auto last = end(customerCounts);

      for (int count : sellCounts)
      {
         //Always attribute goods to big customer (once it went above the threshold)
         count = std::max(0, count - std::distance(begin(customerCounts), endBig));

         //Distribute the rest the most evenly possible
         for (size_t s = 0; s < count; ++s)
         {
            if (nextLow == last) nextLow = endBig;
            *nextLow += 1;
            ++nextLow;
         }

         //Update of the big customers
         endBig = std::find_if(endBig, last, [bigShopperThreshold](int s) { return s < bigShopperThreshold; });
      }

      return std::distance(begin(customerCounts), endBig);
   }
}
