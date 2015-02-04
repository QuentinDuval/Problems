#pragma once

#include "utils/Matrix.h"
#include <vector>


namespace prob
{
   class SudokuPuzzle
   {
   public:
      static const size_t SQUARE_SIZE = 3;
      static const size_t PUZZLE_SIZE = 9;

      using Choices = std::vector<size_t>;
      using Coord = std::pair<size_t, size_t>;
      using Coords = std::vector<Coord>;
      using CoordIt = Coords::const_iterator;

   public:
      SudokuPuzzle(std::initializer_list<size_t> const&);
      ~SudokuPuzzle()= default;

      /** Access the underlying matrix */
      Matrix<size_t> const& puzzle() const;

      /** Get the choices available at (x, y) */
      Choices choicesAt(size_t, size_t) const;

      /** Get the number of back-tracks */
      size_t backtrackCount() const;

      /** Solve the puzzle */
      bool solve();
      bool solveDummy();

   private:
      /** Solve following the order provided as parameter */
      bool solve(CoordIt, CoordIt);

   private:
      Matrix<size_t> m_matrix;
      size_t m_backtrackCount;
   };

   void sudokuTest();
}
