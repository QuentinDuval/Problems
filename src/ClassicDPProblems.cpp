#include "ClassicDPProblems.h"
#include "utils/Matrix.h"


namespace prob
{
   size_t binomialCoeff(size_t k, size_t n)
   {
      Matrix<size_t> m(n + 1, n + 1, 1);
      for (size_t i = 1; i <= n; ++i)
         for (size_t j = 1; j < i && j <= k; ++j)
            m.at(j, i) = m.at(j - 1, i - 1) + m.at(j, i - 1);

      return m.at(k, n);
   }

   //--------------------------------------------------------------------------

   size_t editDistance(std::string const& a, std::string const& b)
   {
      if (a.empty()) return b.size();
      if (b.empty()) return a.size();

      Matrix<size_t> distances(a.size() + 1, b.size() + 1);
      for (size_t i = 0; i < a.size(); ++i)
      {
         for (size_t j = 0; j < b.size(); ++j)
         {
            std::vector<size_t> options(3, 0);
            options[0] = distances.at(i, j) + (a[i] != b[j] ? 1 : 0);
            options[1] = distances.at(i, j + 1) + 1;
            options[2] = distances.at(i + 1, j) + 1;
            distances.at(i + 1, j + 1) = *std::min_element(begin(options), end(options));
         }
      }
      return distances.at(a.size(), b.size());
   }

   //--------------------------------------------------------------------------

   size_t fibo(size_t n)
   {
      if (n == 0)
         return 0;

      size_t prev = 0;
      size_t curr = 1;
      for (size_t i = 1; i < n; ++i)
      {
         size_t next = curr + prev;
         prev = curr;
         curr = next;
      }
      return curr;
   }

   /**
   * --------------------------------------------------------------------------
   * Longest[k] = max of:
   * - max { i < k } { input[k] >= Longest[i] } of Longest[i] + 1
   * - max { i < k } { input[k] <  Longest[i] } of Longest[i]
   * --------------------------------------------------------------------------
   */
   std::vector<double> longestIncreasingSeq(std::vector<double> const& inputs)
   {
      size_t len = inputs.size();
      std::vector<size_t> longest(len + 1, 0);
      std::vector<size_t> previous(len + 1, 0);
      std::vector<double> lastVal(len + 1, std::numeric_limits<double>::min());

      for (size_t i = 0; i < len; ++i)
      {
         for (size_t j = 0; j <= i; ++j)
         {
            size_t incr = lastVal[j] > inputs[i] ? 0 : 1;
            if (longest[j] + incr > longest[i + 1])
            {
               previous[i + 1] = j;
               longest[i + 1] = longest[j] + incr;
               lastVal[i + 1] = incr ? inputs[i] : lastVal[j];
            }
         }
      }

      std::vector<double> out;
      for (size_t i = len; i != 0;)
      {
         size_t p = previous[i];
         if (longest[i] > longest[p])
            out.push_back(lastVal[i]);
         i = p;
      }

      std::reverse(begin(out), end(out));
      return out;
   }


   /**
   * --------------------------------------------------------------------------
   * Observation:
   * 1. This looks a lot like the unbounded knapsack problem (in which you can take as many item as you want)
   * 2. The recursion looks then like the one of this classic problem, with the value of item equal to -1
   *
   * Recursion:
   * - makingChange(0) = 0
   * - makingChange(n) = max (k < n) { 1 + makingChange(n - coins[k]) }
   * --------------------------------------------------------------------------
   */
   size_t makingChange(size_t totalAmount, std::vector<size_t> const& coins)
   {
      static const size_t Infinity = std::numeric_limits<size_t>::max();
      std::vector<size_t> changes(totalAmount + 1, Infinity);
      changes[0] = 0;

      for (size_t amount = 1; amount <= totalAmount; ++amount)
      {
         size_t min = Infinity;
         for (size_t i = 0; i < coins.size(); ++i)
         {
            if (amount < coins[i]) break;
            min = std::min(min, 1 + changes[amount - coins[i]]);
         }
         changes[amount] = min;
      }

      return changes[totalAmount];
   }


   /**
   * --------------------------------------------------------------------------
   * Observation:
   * 1. From the standpoint of the value at k, if the sum of a sub-sequence
   * ending at k-1 is negative positive, there is no reason to add it to k.
   * And if positive, there are no reasons not to add it.
   * 2. We need to keep track of the longuest sub-sequence ending at k-1
   * 3. We need to keep track of the longuest sub-sequence as a whole
   *
   * Recurrence relation:
   *
   * Max[k] = max of (
   * - max subsequence of Max[k-1]
   * - max subsuquence of Max[k-1] ending at k-1 + inputs[k]
   * - sub-sequence made of inputs[k] only (or empty sequence if input[k] < 0)
   * )
   * --------------------------------------------------------------------------
   */
   Range<MaxContiguous::InputIt> MaxContiguous::maxSum(std::vector<double> const& inputs)
   {
      double maxValue = 0;
      InputIt maxBeg = begin(inputs);
      InputIt maxEnd = begin(inputs);

      double maxSuffix = 0;
      InputIt maxSuffixBeg = begin(inputs);

      for (auto it = begin(inputs); it != end(inputs); ++it)
      {
         if (0 < maxSuffix)
         {
            maxSuffix += *it;
         }
         else
         {
            maxSuffix = *it;
            maxSuffixBeg = it;
         }

         if (maxSuffix > maxValue)
         {
            maxValue = maxSuffix;
            maxBeg = maxSuffixBeg;
            maxEnd = it + 1;
         }
      }

      return makeRange(maxBeg, maxEnd);
   }

   //--------------------------------------------------------------------------

   Range<MaxContiguous::InputIt> MaxContiguous::maxProduct(Inputs const& inputs)
   {
      Inputs logInputs(inputs.size());
      transform(inputs, logInputs.begin(), [](double d) { return log(d); });
      auto result = maxSum(logInputs);

      auto b = begin(inputs) + std::distance(cbegin(logInputs), begin(result));
      auto e = begin(inputs) + std::distance(cbegin(logInputs), end(result));
      return makeRange(b, e);
   }

   /**
   * --------------------------------------------------------------------------
   * Sub-dividing the space of search into spaces [i..j]
   * - T[i,j] = numbers of parenthesization from i to j leading to True
   * - F[i,j] = numbers of parenthesization from i to j leading to False
   * 
   * Recurrence:
   * - T[i,i] = 1 if input i is 'T', else 0
   * - G[i,i] = 1 if input i is 'F', else 0
   *
   * - T[i, j+1] = sum { i <= k <= j } of
   *   - "and": T[i, k] * T[k, j+1]
   *   - "xor": T[i, k] * F[k, j+1] + F[i, k] * T[k, j+1]
   *   - "or":  "and" + "xor"
   *
   * - F[i, j+1] = sum { i <= k <= j } of
   *   - "or": F[i, k] * F[k, j+1]
   *   - "xor": T[i, k] * F[k, j+1] + F[i, k] * T[k, j+1]
   *   - "and":  "or" + "xor"
   * --------------------------------------------------------------------------
   */

   size_t BooleanParenthesization::count(Variables const& vs, Connectors const& cs)
   {
      if (vs.empty()) return 0;
      if (vs.size() - 1 != cs.size()) return 0;

      Matrix<size_t> trueNb (vs.size(), vs.size(), 0);
      Matrix<size_t> falseNb(vs.size(), vs.size(), 0);
      for (size_t v = 0; v < vs.size(); ++v)
      {
         if (vs[v]) trueNb.at(v, v) = 1;
         else       falseNb.at(v, v) = 1;
      }

      for (size_t gap = 1; gap < vs.size(); ++gap)
      {
         for (size_t i = 0; i < vs.size() - gap; ++i)
         {
            size_t j = i + gap;
            for (size_t k = i; k < j; ++k)
            {
               const auto& c = cs[k];
               if (c != "xor")
               {
                  trueNb.at(i, j) += trueNb.at(i, k) * trueNb.at(k + 1, j);
                  falseNb.at(i, j) += falseNb.at(i, k) * falseNb.at(k + 1, j);
               }
               if (c != "and")
               {
                  trueNb.at(i, j) += trueNb.at(i, k) * falseNb.at(k + 1, j);
                  trueNb.at(i, j) += falseNb.at(i, k) * trueNb.at(k + 1, j);
               }
               if (c != "or")
               {
                  falseNb.at(i, j) += trueNb.at(i, k) * falseNb.at(k + 1, j);
                  falseNb.at(i, j) += falseNb.at(i, k) * trueNb.at(k + 1, j);
               }
            }
         }
      }

      return trueNb.at(0, vs.size() - 1);
   }

   //--------------------------------------------------------------------------

   size_t longestZigZag(std::vector<int> const& sequence, bool increaseByDefault)
   {
      if (sequence.empty())
         return 0;

      std::vector<size_t> longest(sequence.size(), 1);
      std::vector<bool> lastWasIncrease(sequence.size(), increaseByDefault);

      for (size_t curr = 1; curr < sequence.size(); ++curr)
      {
         for (size_t prev = 0; prev < curr; ++prev)
         {
            //Do not waste time
            if (longest[prev] < longest[curr])
               continue;

            if ((sequence[prev] > sequence[curr] && lastWasIncrease[prev])
             || (sequence[prev] < sequence[curr] && !lastWasIncrease[prev]))
            {
               longest[curr] = longest[prev] + 1;
               lastWasIncrease[curr] = !lastWasIncrease[prev];
            }
         }
      }

      return *std::max_element(begin(longest), end(longest));
   }

   size_t ZigZag::longest(std::vector<int> const& sequence)
   {
      size_t withZag = longestZigZag(sequence, true);
      size_t withZig = longestZigZag(sequence, false);
      return std::max(withZag, withZig);
   }

   //--------------------------------------------------------------------------

   static bool intersect(int b1, int w1, int b2, int w2)
   {
      if (b1 <= b2 && b2 <= w1) return true;
      if (b1 <= w2 && w2 <= w1) return true;
      if (b2 <= b1 && b1 <= w2) return true;
      if (b2 <= w1 && w1 <= w2) return true;
      return false;
   }

   FlowerGarden::Ints FlowerGarden::getOrdering(Ints heights, Ints blooms, Ints wilts)
   {
      if (heights.empty())
         return Ints();

      for (size_t f = 1; f < heights.size(); ++f)
      {
         int h = heights[f];
         auto b = blooms[f];
         auto w = wilts[f];

         size_t lowerBound = 0;
         size_t upperBound = f;
         for (size_t i = 0; i < f; ++i)
         {
            if (!intersect(b, w, blooms[i], wilts[i]))
               continue;

            if (h > heights[i])
            {
               lowerBound = i + 1;
            }
            else
            {
               upperBound = i;
               break;
            }
         }

         size_t i = lowerBound;
         for (; i < upperBound; ++i)
         {
            if (h > heights[i])
               break;
         }

         if (i != f)
         {
            std::rotate(begin(heights) + i, begin(heights) + f, begin(heights) + f + 1);
            std::rotate(begin(blooms) + i, begin(blooms) + f, begin(blooms) + f + 1);
            std::rotate(begin(wilts) + i, begin(wilts) + f, begin(wilts) + f + 1);
         }
      }

      return heights;
   }

   //--------------------------------------------------------------------------

   size_t CollectingApples::findMax(Matrix<size_t> const& field)
   {
      Matrix<size_t> bestCounts(field.width(), field.height(), 0);
      bestCounts.at(0, 0) = field.at(0, 0);

      for (size_t x = 0; x < field.width(); ++x)
      {
         for (size_t y = 0; y < field.height(); ++y)
         {
            auto& best = bestCounts.at(x, y);
            if (x > 0) best = std::max(best, bestCounts.at(x - 1, y) + field.at(x, y));
            if (y > 0) best = std::max(best, bestCounts.at(x, y - 1) + field.at(x, y));
         }
      }
      return bestCounts.at(field.width() - 1, field.height() - 1);
   }

   //--------------------------------------------------------------------------

   std::vector<size_t> TaskPartitioning::find(std::vector<int> const& costs, size_t partitionCount)
   {
      std::vector<size_t> sumTo(costs.size(), costs[0]);
      for (size_t i = 1; i < costs.size(); ++i)
         sumTo[i] = sumTo[i - 1] + costs[i];

      Matrix<size_t> maxPartVal(costs.size(), partitionCount, 0);
      Matrix<size_t> maxPartPoint(costs.size(), partitionCount);

      for (size_t i = 0; i < costs.size(); ++i)
         maxPartVal.at(i, 0) = sumTo[i];

      for (size_t p = 1; p < partitionCount; ++p)
      {
         for (size_t n = p; n < costs.size(); ++n)
         {
            size_t partPoint = 0;
            size_t best = std::numeric_limits<size_t>::max();

            for (size_t k = p - 1; k < n; ++k)
            {
               size_t val = std::max(maxPartVal.at(k, p - 1), sumTo[n] - sumTo[k]);
               if (val < best)
               {
                  best = val;
                  partPoint = k;
               }
            }

            maxPartVal.at(n, p) = best;
            maxPartPoint.at(n, p) = partPoint;
         }
      }

      std::vector<size_t> partPoints;
      size_t point = maxPartPoint.at(costs.size() - 1, partitionCount - 1);
      for (size_t p = 1; p < partitionCount; ++p)
      {
         partPoints.push_back(point);
         point = maxPartPoint.at(point, partitionCount - p - 1);
      }
      return partPoints;
   }
}
