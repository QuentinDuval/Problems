#pragma once

#include <random>
#include <string>
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


   /** Spell a number in text for an integer taken between 0 and 1 million excluded */
   std::string spellNumber(int);


   /** Randomly shuffle a list of objects based on a single number generator */
   template<typename T>
   void randomShuffle(std::vector<T>& values)
   {
      std::random_device rd;
      std::mt19937 g(rd());
      for (size_t i = 0; i < values.size(); ++i)
      {
         std::uniform_int_distribution<size_t> distribution(i, values.size() - 1);
         size_t j = distribution(g);
         std::swap(values[i], values[j]);
      }
   }
}
