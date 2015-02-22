#include "GraphProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <iterator>
#include <set>
#include <vector>


namespace prob
{
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
   // DOUBLE TREE
   //--------------------------------------------------------------------------

   static std::vector<DoubleTree::Nodes> makeTree(DoubleTree::Nodes const& src, DoubleTree::Nodes const& dst)
   {
      std::vector<DoubleTree::Nodes> tree(src.size() + 1);
      for (size_t i = 0; i < src.size(); ++i)
      {
         tree[src[i]].push_back(dst[i]);
         tree[dst[i]].push_back(src[i]);
      }
      return tree;
   }

   struct DoubleTreeImpl
   {
      DoubleTreeImpl(std::vector<int> const& values) : m_values(values) {}
      std::vector<int> const& m_values;
      using Nodes = DoubleTree::Nodes;

      int maxScore(std::vector<Nodes> const& tree1, std::vector<Nodes> const& tree2, int root)
      {
         Nodes selected(1, root);
         return maxScore(tree1, tree2, selected);
      }

      int maxScore(std::vector<Nodes> const& tree1, std::vector<Nodes> const& tree2, Nodes& selected)
      {
         int root = selected.back();
         int bestScore = m_values[root];
         for (int next : tree1[root])
         {
            if (contains(selected, next) || !contains(tree2[root], next))
               continue;

            selected.push_back(next);
            int incr = maxScore(tree1, tree2, selected);
            if (incr > 0)
               bestScore += incr;
            else
               selected.pop_back();
         }
         return bestScore;
      }

      static bool contains(Nodes const& nodes, int n)
      {
         return end(nodes) != std::find(begin(nodes), end(nodes), n);
      }
   };

   int DoubleTree::maximalScore(Nodes const& src1, Nodes const& dst1, Nodes const& src2, Nodes const& dst2, std::vector<int> const& values)
   {
      //Contruct the trees
      std::vector<Nodes> tree1 = makeTree(src1, dst1);
      std::vector<Nodes> tree2 = makeTree(src2, dst2);
      const size_t n = tree1.size();

      //Try all possible roots
      int best = std::numeric_limits<int>::min();
      DoubleTreeImpl doubleTreeImpl(values);
      for (int root = 0; root < n; ++root)
         best = std::max(best, doubleTreeImpl.maxScore(tree1, tree2, root));
      return best;
   }
}
