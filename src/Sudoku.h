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

   public:
      SudokuPuzzle(std::initializer_list<size_t> const&);
      ~SudokuPuzzle()= default;

      /** Access the underlying matrix */
      Matrix<size_t> const& puzzle() const;

      /** Get the choices available at (x, y) */
      Choices choicesAt(size_t, size_t) const;

      /** Solve the puzzle */
      bool solve();
      bool solve(size_t x);

   private:
      Matrix<size_t> m_matrix;
   };

   void sudokuTest();
}
