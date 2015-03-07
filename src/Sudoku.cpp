#include "Sudoku.h"

#include "utils/Algorithms.h"
#include "utils/Functors.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   SudokuPuzzle::SudokuPuzzle(std::initializer_list<size_t> const& init)
      : m_matrix(PUZZLE_SIZE, PUZZLE_SIZE, init)
      , m_backtrackCount(0)
   {}

   utils::Matrix<size_t> const& SudokuPuzzle::puzzle() const
   {
      return m_matrix;
   }

   size_t SudokuPuzzle::backtrackCount() const
   {
      return m_backtrackCount;
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
         utils::erase(choices, m_matrix.at(x, i));
         utils::erase(choices, m_matrix.at(i, y));
      }

      //Remove from the square
      size_t sx = squareCoord(x);
      size_t sy = squareCoord(y);
      for (size_t i = sx; i < sx + SQUARE_SIZE; ++i)
         for (size_t j = sy; j < sy + SQUARE_SIZE; ++j)
            utils::erase(choices, m_matrix.at(i, j));

      return choices;
   }

   bool SudokuPuzzle::solve()
   {
      std::vector<std::pair<size_t, size_t>> toFill;
      utils::Matrix<Choices> choices(PUZZLE_SIZE, PUZZLE_SIZE);

      for (size_t y = 0; y < PUZZLE_SIZE; ++y)
      {
         for (size_t x = 0; x < PUZZLE_SIZE; ++x)
         {
            auto val = m_matrix.at(x, y);
            if (val)
               continue;

            toFill.emplace_back(x, y);
            choices.at(x, y) = choicesAt(x, y);
         }
      }

      utils::sortBy(toFill, utils::comparingWith([&](Coord const& c) { return choices.at(c.first, c.second).size(); }));
      return solve(begin(toFill), end(toFill));
   }

   bool SudokuPuzzle::solveDummy()
   {
      std::vector<std::pair<size_t, size_t>> toFill;
      for (size_t y = 0; y < PUZZLE_SIZE; ++y)
      {
         for (size_t x = 0; x < PUZZLE_SIZE; ++x)
         {
            auto val = m_matrix.at(x, y);
            if (!val)
               toFill.emplace_back(x, y);
         }
      }
      return solve(begin(toFill), end(toFill));
   }

   bool SudokuPuzzle::solve(CoordIt b, CoordIt e)
   {
      if (b == e)
         return true;

      size_t x = b->first;
      size_t y = b->second;
      if (m_matrix.at(x, y))
         return solve(b + 1, e);

      Choices cs = choicesAt(x, y);
      if (cs.empty())
         return false;

      for (auto c : cs)
      {
         m_matrix.at(x, y) = c;
         if (solve(b + 1, e))
            return true;
         ++m_backtrackCount;
         m_matrix.at(x, y) = 0;
      }
      return false;
   }


   //------------------------------------------------------------------------------------

   template<typename ResolutionMethod>
   void sudokuTest(SudokuPuzzle puzzle, SudokuPuzzle const& expected, ResolutionMethod solve)
   {
      bool success = solve(puzzle);
      std::cout << " - " << (success ? "success" : "failure") << " with " << puzzle.backtrackCount() << " backtracks." << std::endl;
      assert(expected.puzzle() == puzzle.puzzle());
   }

   void sudokuTest()
   {
      std::cout << std::endl << "[Sudoku tests]" << std::endl;

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

      std::cout << std::endl << "* No specific evaluation order:" << std::endl;
      sudokuTest(puzzle, solution, [](SudokuPuzzle& p) { return p.solveDummy(); });

      std::cout << std::endl << "* Element with lowest choices first:" << std::endl;
      sudokuTest(puzzle, solution, [](SudokuPuzzle& p) { return p.solve(); });
   }
}
