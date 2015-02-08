#include "StringProblems.h"
#include "utils/Algorithms.h"
#include "utils/Matrix.h"

#include <assert.h>
#include <iostream>


namespace prob
{
   WordSplit::WordSplit(Dict const& dict)
      : m_dict(dict)
   {}

   std::vector<std::string> WordSplit::splitInWords(std::string const& input)
   {
      size_t lastSplit = 0;
      std::vector<std::string> splits;

      for (size_t i = 1; i <= input.size(); ++i)
      {
         std::string temp(input.begin() + lastSplit, input.begin() + i);
         if (m_dict.find(temp) != end(m_dict))
         {
            lastSplit = i;
            splits.emplace_back(std::move(temp));
         }
      }

      if (lastSplit != input.size())
         return std::vector<std::string>();
      return splits;
   }


   //--------------------------------------------------------------------------
   // DOUBLE LETTERS
   //--------------------------------------------------------------------------

   bool doubleLetter(std::string const& s)
   {
      if (s.empty())
         return true;

      size_t prev = 0;
      size_t curr = 1;
      std::vector<bool> marked(s.size() + 1, false);

      for (; curr <= s.size(); ++curr)
      {
         if (prev != 0 && s[curr - 1] == s[prev - 1])
         {
            marked[curr] = true;
            marked[prev] = true;
            do { --prev; } while (marked[prev]);
         }
         else
         {
            prev = curr;
         }
      }

      return end(marked) == std::find(begin(marked) + 1, end(marked), false);
   }


   //--------------------------------------------------------------------------
   // Parentheses
   //--------------------------------------------------------------------------

   std::vector<std::string> Parentheses::combinationNb(size_t nbPairs)
   {
      std::vector<std::string> combinations;
      if (nbPairs == 0) return combinations;
      if (nbPairs == 1) return { "()" };

      for (auto&s : combinationNb(nbPairs - 1))
      {
         combinations.push_back(s + "()");
         combinations.push_back("(" + s + ")");
      }
      return combinations;
   }
   

   //--------------------------------------------------------------------------
   // BRACKET EXPRESSIONS
   // 
   // 1. Brute force approach: have a way to check the correctness of an
   // epxression and try all X replacement, which means 6^X possibilities.
   // Because X is given as lower than 5 in the problem it can be done.
   // 
   // 2. Other approach is to maintain a stack of open parentheses.
   // If a X is found, then we can make it lower a stack level, or increase it.
   // It should lower the worst number of attempt to 4^X.
   //
   //--------------------------------------------------------------------------

   struct Brackets
   {
      using string_it = std::string::iterator;

      static bool isClosing(char c1, char c2)
      {
         if (c1 == '(' && c2 == ')') return true;
         if (c1 == '[' && c2 == ']') return true;
         if (c1 == '{' && c2 == '}') return true;
         return false;
      }

      static bool isValid(std::string const& expr)
      {
         std::vector<char> stack;
         for (char c : expr)
         {
            if (c == '(' || c == '[' || c == '{')
               stack.push_back(c);
            else if (stack.empty())
               return false;
            else if (isClosing(stack.back(), c))
               stack.pop_back();
            else
               return false;
         }
         return stack.empty();
      }

      static bool bruteForce(std::string& expr, string_it it)
      {
         it = std::find(it, end(expr), 'X');
         if (it == expr.end())
            return isValid(expr);

         static const char possibles[] = { '(', '[', '{', '}', ']', ')' };
         for (char c : possibles)
         {
            *it = c;
            if (bruteForce(expr, it + 1))
               return true;
            *it = 'X';
         }
         return false;
      }
   };

   bool BracketExpressions::isPossible(std::string const& expr)
   {
      std::string expression = expr;
      return Brackets::bruteForce(expression, begin(expression));
   }


   //--------------------------------------------------------------------------
   // TARO STRING
   //--------------------------------------------------------------------------

   bool TaroString::getAnswer(std::string const& s)
   {
      std::string cleanedS = s;
      eraseIf(cleanedS, [](char c){ return c != 'C' && c != 'A' && c != 'T'; });
      return cleanedS == "CAT";
   }
}
