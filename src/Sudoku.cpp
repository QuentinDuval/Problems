#include "Sudoku.h"

#include "utils/Algorithms.h"
#include <iostream>


namespace prob
{
   SudokuPuzzle::SudokuPuzzle(std::initializer_list<size_t> const& init)
      : m_matrix(PUZZLE_SIZE, PUZZLE_SIZE, init)
   {}

   Matrix<size_t> const& SudokuPuzzle::puzzle() const
   {
      return m_matrix;
   }

   static size_t squareCoord(size_t x)
   {
      return x - (x % SudokuPuzzle::SQUARE_SIZE);
   }

   SudokuPuzzle::Choices SudokuPuzzle::choicesAt(size_t x, size_t y) const
   {
      Choices choices { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

      //Remove from the lines
      for (size_t i = 0; i < PUZZLE_SIZE; ++i)
      {
         erase(choices, m_matrix.at(x, i));
         erase(choices, m_matrix.at(i, y));
      }

      //Remove from the square
      size_t sx = squareCoord(x);
      size_t sy = squareCoord(y);
      for (size_t i = sx; i < sx + SQUARE_SIZE; ++i)
         for (size_t j = sy; j < sy + SQUARE_SIZE; ++j)
            erase(choices, m_matrix.at(i, j));

      return choices;
   }

   bool SudokuPuzzle::solve()
   {
      return solve(0);
   }

   bool SudokuPuzzle::solve(size_t p)
   {
      if (p == PUZZLE_SIZE * PUZZLE_SIZE)
         return true;

      size_t x = p % PUZZLE_SIZE;
      size_t y = p / PUZZLE_SIZE;
      if (m_matrix.at(x, y))
         return solve(p + 1);

      Choices cs = choicesAt(x, y);
      if (cs.empty())
         return false;

      for (auto c : cs)
      {
         m_matrix.at(x, y) = c;
         if (solve(p + 1))
            return true;
         m_matrix.at(x, y) = 0;
      }
      return false;
   }


   //------------------------------------------------------------------------------------

   void sudokuTest()
   {
      std::cout << std::endl << "Sudoku tests" << std::endl;

      SudokuPuzzle puzzle =
      {
         5, 3, 0,   0, 7, 0,   0, 0, 0,
         6, 0, 0,   1, 9, 5,   0, 0, 0,
         0, 9, 8,   0, 0, 0,   0, 6, 0,
                               
         8, 0, 0,   0, 6, 0,   0, 0, 3,
         4, 0, 0,   8, 0, 3,   0, 0, 1,
         7, 0, 0,   0, 2, 0,   0, 0, 6,
                               
         0, 6, 0,   0, 0, 0,   2, 8, 0,
         0, 0, 0,   4, 1, 9,   0, 0, 5,
         0, 0, 0,   0, 8, 0,   0, 7, 9
      };

      for (auto c : puzzle.choicesAt(2, 0))
         std::cout << c << std::endl;

      bool success = puzzle.solve();
      std::cout << (success ? "success" : "failure") << std::endl;

      SudokuPuzzle solution =
      {
         5, 3, 4,   6, 7, 8,   9, 1, 2,
         6, 7, 2,   1, 9, 5,   3, 4, 8,
         1, 9, 8,   3, 4, 2,   5, 6, 7,
                               
         8, 5, 9,   7, 6, 1,   4, 2, 3,
         4, 2, 6,   8, 5, 3,   7, 9, 1,
         7, 1, 3,   9, 2, 4,   8, 5, 6,
                               
         9, 6, 1,   5, 3, 7,   2, 8, 4,
         2, 8, 7,   4, 1, 9,   6, 3, 5,
         3, 4, 5,   2, 8, 6,   1, 7, 9
      };

      if (solution.puzzle() == puzzle.puzzle())
         std::cout << "ok" << std::endl;
   }
}
