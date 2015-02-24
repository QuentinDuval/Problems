#include "GraphProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <functional>
#include <iterator>
#include <queue>
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
            if (contains(selected, next) || !reachableFrom(tree2, selected, next))
               continue;

            selected.push_back(next);
            int incr = maxScore(tree1, tree2, selected);
            if (incr > 0)
               bestScore += incr;
            else
               selected.pop_back();
         }
         return std::max(0, bestScore);
      }

      static bool reachableFrom(std::vector<Nodes> const& tree, Nodes& selected, int searched)
      {
         //TODO - Use DFS on tree 2 instead...
         for (int node : selected)
         {
            if (contains(tree[node], searched))
               return true;
         }
         return false;
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


   //--------------------------------------------------------------------------
   // FAMILY
   //--------------------------------------------------------------------------

   class DFS
   {
   public:
      using Graph = std::vector<std::vector<int>>;

      DFS(Graph const& graph)
         : m_graph(graph)
         , m_marked(graph.size(), false)
         , m_gender(graph.size(), false)
      {}

      void searchFrom(int from, std::function<void()> onImpossible, bool gender = false)
      {
         if (m_marked[from])
         {
            if (m_gender[from] != gender)
               onImpossible();
            return;
         }

         m_marked[from] = true;
         m_gender[from] = gender;
         for (int adjacent : m_graph[from])
            searchFrom(adjacent, onImpossible, !gender);
      }

   private:
      Graph const& m_graph;
      std::vector<bool> m_marked;
      std::vector<bool> m_gender;
   };


   bool Family::isFamily(std::vector<int> const& parent1, std::vector<int> const& parent2)
   {
      //What is insteresting here are the relationship between the parents, so let us build a graph for this
      std::vector<std::vector<int>> parentRelations(parent1.size());
      for (size_t p = 0; p < parent1.size(); ++p)
      {
         if (parent1[p] == -1 || parent2[p] == -1)
            continue;

         parentRelations[parent1[p]].push_back(parent2[p]);
         parentRelations[parent2[p]].push_back(parent1[p]);
      }

      //What we need to find is cycles between the parents
      //If the cycles are made of an event number of parents, then we cannot have a family tree
      for (int v = 0; v < parentRelations.size(); ++v)
      {
         bool impairCycle = false;
         DFS dfs(parentRelations);
         dfs.searchFrom(v, [&impairCycle]() { impairCycle = true; });
         if (impairCycle)
            return false;
      }
      return true;
   }


   //--------------------------------------------------------------------------
   // HEXAGONAL BOARD
   //--------------------------------------------------------------------------

   static std::vector<int> adjacents(int coord, int size)
   {
      int x = coord % size;
      int y = coord / size;
      std::vector<std::pair<int, int>> adjPoints{
         { x - 1, y }, { x, y - 1 }, { x + 1, y - 1 },
         { x - 1, y + 1 }, { x, y + 1 }, { x + 1, y } };

      std::vector<int> adjList;
      for (size_t i = 0; i < adjPoints.size(); ++i)
      {
         auto& p = adjPoints[i];
         if (0 <= p.first && p.first < size && 0 <= p.second && p.second < size)
            adjList.push_back(p.first + size * p.second);
      }
      return adjList;
   }

   int HexagonalBoard::minColors(std::vector<std::string> const& board)
   {
      //Identify the cells that should be colored
      int size = board.size();
      std::vector<bool> toColor(size * size, false);
      for (int y = 0; y < size; ++y)
      {
         for (int x = 0; x < size; ++x)
         {
            toColor.at(x + size * y) = 'X' == board[y][x];
         }
      }

      //If there are no vertices to color, no colors are needed
      if (end(toColor) == std::find(begin(toColor), end(toColor), true))
         return 0;

      //Build the graph, but only add the element in the board we care about
      std::vector<std::vector<int>> graph(toColor.size());
      for (int v = 0; v < toColor.size(); ++v)
      {
         if (!toColor[v])
            continue;

         std::vector<int> adjList = adjacents(v, size);
         auto last = std::remove_if(begin(adjList), end(adjList), [&](int w) { return !toColor[w]; });
         std::copy(begin(adjList), last, std::back_inserter(graph[v]));
      }

      //If there are no links between vertices, then we need 1 color
      if (std::all_of(begin(graph), end(graph), [](std::vector<int> const& adjList) { return adjList.empty(); }))
         return 1;

      //If we can two color the vertex (via dfs), then we need 2 colors, otherwise we need 3 colors at most
      for (int v = 0; v < toColor.size(); ++v)
      {
         DFS dfs(graph);
         bool twoColorable = true;
         dfs.searchFrom(v, [&]() { twoColorable = false; });
         if (!twoColorable)
            return 3;
      }
      return 2;
   }


   //--------------------------------------------------------------------------
   // EGALITARIANISM
   //--------------------------------------------------------------------------

   class EgalitarianismBFS
   {
   public:
      using Graph = std::vector<std::vector<size_t>>;

   public:
      explicit EgalitarianismBFS(Graph const& graph)
         : m_graph(graph)
         , m_marked(graph.size(), false)
         , m_distanceTo(graph.size(), std::numeric_limits<size_t>::max())
      {}

      void searchFrom(size_t vertex)
      {
         std::queue<size_t> queue;
         m_distanceTo[vertex] = 0;
         queue.push(vertex);

         while (!queue.empty())
         {
            size_t curr = queue.front();
            queue.pop();
            m_marked[curr] = true;

            for (size_t adj : m_graph[curr])
            if (!m_marked[adj])
            {
               m_distanceTo[adj] = m_distanceTo[curr] + 1;
               queue.push(adj);
            }
         }
      }

      bool isConnected() const
      {
         return end(m_marked) == std::find(begin(m_marked), end(m_marked), false);
      }

      size_t maxDistance() const
      {
         return *std::max_element(begin(m_distanceTo), end(m_distanceTo));
      }

   private:
      Graph const& m_graph;
      std::vector<bool> m_marked;
      std::vector<size_t> m_distanceTo;
   };

   int Egalitarianism::maxDifference(std::vector<std::string> const& isFriend, int diff)
   {
      //Build the friendship graph
      size_t citizenCount = isFriend.size();
      std::vector<std::vector<size_t>> friendGraph(citizenCount);
      for (size_t i = 0; i < citizenCount; ++i)
      for (size_t j = 0; j < citizenCount; ++j)
      {
         if ('Y' == isFriend[i][j])
            friendGraph[i].push_back(j);
      }

      //Compute the max difference
      EgalitarianismBFS bfs(friendGraph);
      bfs.searchFrom(0);
      if (!bfs.isConnected())
         return -1;

      return bfs.maxDistance() * diff;
   }
}
