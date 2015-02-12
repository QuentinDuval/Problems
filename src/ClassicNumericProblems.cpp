#include "ClassicNumericProblems.h"

#include "utils/Algorithms.h"
#include "utils/Functors.h"

#include <array>
#include <iterator>
#include <limits>
#include <set>
#include <sstream>


namespace prob
{
   static size_t gcdImpl(size_t g, size_t l)
   {
      if (l == 0) return g;
      return gcdImpl(l, g % l);
   }

   size_t gcd(size_t a, size_t b)
   {
      return gcdImpl(std::max(a, b), std::min(a, b));
   }

   //--------------------------------------------------------------------------

   static double square(double d)
   {
      return d * d;
   }

   static double getDistance(ClosestPairs::Point const& p1, ClosestPairs::Point const& p2)
   {
      return sqrt(square(p1.first - p2.first) + square(p1.second - p2.second));
   }

   std::pair<ClosestPairs::Point, ClosestPairs::Point> ClosestPairs::find(std::vector<Point> const& ps)
   {
      std::pair<Point, Point> minPair;
      if (ps.size() < 2)
         return minPair;

      std::vector<Point> sortedPoints(ps);
      sortBy(sortedPoints, comparingWith(GetFirst()));

      auto compareY = comparingWith(GetSecond());
      std::multiset<Point, decltype(compareY)> closest(compareY);
      closest.insert(sortedPoints[0]);
      double minDist = std::numeric_limits<double>::max();

      for (size_t i = 1; i < sortedPoints.size(); ++i)
      {
         //Get rid of points whose X delta is higher than the minimal distance
         Point const& p = sortedPoints[i];
         for (auto it = begin(closest); it != end(closest);)
         {
            auto current = it++;
            if (current->first < p.first - minDist)
               closest.erase(current);
         }

         //Only search among the points whose Y delta is lower than the minimal distance
         Point low = Point(0, p.second - minDist);
         Point high = Point(0, p.second + minDist);
         for (auto it = closest.lower_bound(low); it != closest.upper_bound(high); ++it)
         {
            double dist = getDistance(*it, p);
            if (dist < minDist)
            {
               minPair = std::make_pair(*it, p);
               minDist = dist;
            }
         }

         closest.insert(p);
      }

      return minPair;
   }

   //--------------------------------------------------------------------------

   namespace
   {
      struct IntersectionEvent
      {
         enum type { HStart, VLine, HEnd };

         type m_type;
         double m_xCoord;
         LineIntersection::Segment m_segment; //verticalLine event only
      };
   }

   std::vector<LineIntersection::Point> LineIntersection::intersections(std::vector<HLine> const& hLines, std::vector<VLine> const& vLines)
   {
      std::vector<IntersectionEvent> events;
      for (auto& l : hLines)
      {
         Segment s{ l.m_y, l.m_y };
         events.push_back({ IntersectionEvent::HStart, l.m_segment.m_start, s });
         events.push_back({ IntersectionEvent::HEnd,   l.m_segment.m_end, s });
      }
      for (auto& l : vLines)
      {
         events.push_back({ IntersectionEvent::VLine, l.m_x, l.m_segment });
      }

      //Sort by x coordinate, but by type too as start should be considered before vertical lines, and ends after
      sortBy(events, comparingWith([](IntersectionEvent const& e) { return std::make_pair(e.m_xCoord, e.m_type); }));

      std::set<double> validHLines;
      std::vector<Point> intersections;
      for (auto& e : events)
      {
         switch (e.m_type)
         {
         case IntersectionEvent::HStart:
            validHLines.insert(e.m_segment.m_start);
            break;
         case IntersectionEvent::HEnd:
            validHLines.erase(e.m_segment.m_start);
            break;
         case IntersectionEvent::VLine:
            for (auto it = validHLines.lower_bound(e.m_segment.m_start); it != validHLines.upper_bound(e.m_segment.m_end); ++it)
               intersections.emplace_back(e.m_xCoord, *it);
            break;
         }
      }

      return intersections;
   }

   //--------------------------------------------------------------------------

   static std::string digitToStr(int i)
   {
      static std::array<std::string, 10> str = { "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
      return str[i];
   }

   static std::string twoDigitsToStr(int i)
   {
      static std::array<std::string, 10> tens = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fiveteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
      static std::array<std::string, 8> secondDigit = { "Twenty", "Thirty", "Fourty", "Fivety", "Sixty", "Seventy", "Eighty", "Ninety" };

      int d = i / 10;
      int u = i % 10;
      if (d == 0) return digitToStr(i);
      if (d == 1) return tens[u];
      
      auto s = secondDigit[d - 2];
      if (u) s += digitToStr(u);
      return s;
   }

   static void spellShortNb(std::ostream& os, int i)
   {
      int h = i / 100;
      int d = (i % 100);
      os << digitToStr(h) << " Hundred and " << twoDigitsToStr(d);
   }

   std::string spellNumber(int i)
   {
      if (i < 0 || i > 1e6)
         return "I can't spell this";

      int belowThousand = i % 1000;
      int aboveThousand = i / 1000;

      std::ostringstream output;
      spellShortNb(output, aboveThousand);
      output << " Thousands, ";
      spellShortNb(output, belowThousand);
      return output.str();
   }
}
