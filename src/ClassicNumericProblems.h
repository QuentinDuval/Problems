#pragma once
#include <utility>
#include <vector>


namespace prob
{
   /** Return the greater common divisor */
   size_t gcd(size_t a, size_t b);


   /** Return the closest pairs from a set of points */
   struct ClosestPairs
   {
      using Point = std::pair<double, double>;
      static std::pair<Point, Point> find(std::vector<Point> const&);
   };


   /**
    * Indicates if horizontal lines cross some vertical lines.
    * We assume that no lines supperposes
    */
   struct LineIntersection
   {
      using Point = std::pair<double, double>;
      struct Segment { double m_start; double m_end; };
      struct HLine { double m_y; Segment m_segment; };
      struct VLine { double m_x; Segment m_segment; };

      static std::vector<Point> intersections(std::vector<HLine> const&, std::vector<VLine> const&);
   };
}
