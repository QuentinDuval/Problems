#pragma once

#include <queue>
#include <string>
#include <utility>
#include <vector>


namespace prob
{
   /**
    * BuildingRoutes
    * http://community.topcoder.com/stat?c=problem_statement&pm=13193
    */
   struct BuildingRoutes
   {
      static int build(std::vector<std::string> const& distances, int safeThreshold);
   };

   /**
    * DoubleTree
    * http://community.topcoder.com/stat?c=problem_statement&pm=13359
    */
   struct DoubleTree
   {
      using Nodes = std::vector<int>;
      static int maximalScore(Nodes const& src1, Nodes const& dst1, Nodes const& src2, Nodes const& dst2, std::vector<int> const& values);
   };

   /**
    * Family
    * http://community.topcoder.com/stat?c=problem_statement&pm=10541
    */
   struct Family
   {
      static bool isFamily(std::vector<int> const& parent1, std::vector<int> const& parent2);
   };

   /**
    * HexagonalBoard
    * http://community.topcoder.com/stat?c=problem_statement&pm=12784
    */
   struct HexagonalBoard
   {
      static int minColors(std::vector<std::string> const& board);
   };

   /**
    * Egalitarianism
    * http://community.topcoder.com/stat?c=problem_statement&pm=12613
    */
   struct Egalitarianism
   {
      static int maxDifference(std::vector<std::string> const& isFriend, int diff);
   };

   /**
    * DancingFoxes
    * http://community.topcoder.com/stat?c=problem_statement&pm=12548
    */
   struct DancingFoxes
   {
      static int minimalDays(std::vector<std::string> const& friendship);
   };

   /**
   * ---------------------------------------------------------------
   * MaliciousPath
   * http://community.topcoder.com/stat?c=problem_statement&pm=13596
   * ---------------------------------------------------------------
   *
   * Alice will always to to select the shortest path and Bob will selectively use token to disturb this path
   * 1. We start by computing the shortest path from every point to the destination (node N-1).
   *    To do this a single Dijkstra is enough (if you create the reverse graph)
   * 2. Then we proceed by dynamic programming, computing the shortest cost from all vertices to N-1, with an increasing number of token K:
   *    - At iteration K = 0, the cost of the path from each vertices to N-1 is simply the shortest path
   *    - At iteration K + 1, for every vertex V, we look at its neighnors, and compute the cost as
   *      cost(V, K+1) = max [U having an edge to V] { cost(edge(U, V)) + cost(U, K) + cost(V, K) }
   */
   struct MaliciousPath
   {
      static long minPath(int N, int K, std::vector<int> const& from, std::vector<int> const& to, std::vector<int> const& cost);

      struct WeightedEdge
      {
         WeightedEdge(int to, int cost) : m_to(to), m_cost(cost) {}
         int m_to;
         int m_cost;
      };

      using Graph = std::vector<std::vector<WeightedEdge>>;

   private:
      static void shortestPathsFrom(Graph const& graph, int source, std::vector<long>& shortestLen, std::vector<long>& nbLinks, std::vector<int>& prevOnPath);
   };
}
