#include "StringProblems.h"
#include "utils/Algorithms.h"
#include "utils/Functors.h"
#include "utils/Matrix.h"

#include <iterator>
#include <set>


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


   //--------------------------------------------------------------------------
   // WOLF DELAY MASTER
   //--------------------------------------------------------------------------

   bool wolfIsValid(std::string const& str, std::string::const_iterator first)
   {
      if (first == str.end())
         return true;

      auto it = first;
      while (it != str.end() && *it == 'w')
         ++it;

      size_t wNb = std::distance(first, it);
      if (wNb == 0)
         return false;

      if (std::distance(it, str.end()) < 3 * wNb)
         return false;

      for (auto c : { 'o', 'l', 'f' })
      {
         if (wNb != std::count(it, it + wNb, c))
            return false;
         it += wNb;
      }

      return wolfIsValid(str, it);
   }

   bool WolfDelaymaster::isValid(std::string const& str)
   {
      return wolfIsValid(str, str.begin());
   }

   //--------------------------------------------------------------------------

   IPv444::Addr IPv444::parseAddress(std::string const& request)
   {
      Addr out;
      size_t start = 0;
      for (size_t i = 0; i < 4; ++i)
      {
         size_t end = start + 1;
         while (end != request.size() && request[end] != '.')
            ++end;

         std::string subStr = request.substr(start, end - start);
         if (subStr == "*")
            out[i] = -1;
         else
            out[i] = atoi(subStr.c_str());
         start = end + 1;
      }
      return out;
   }

   long long maxAmountRec(std::vector<IPv444::AddrPrice> const& pricedRequests, size_t depth)
   {
      if (pricedRequests.empty())
         return 0;

      if (depth == 4)
         return maxBy(pricedRequests, comparingWith(GetSecond()))->second;

      std::set<int> addrParts;
      for (auto& r : pricedRequests)
         addrParts.insert(r.first[depth]);

      long long amount = 0;
      for (int a : addrParts)
      {
         std::vector<IPv444::AddrPrice> matchingReqs;
         for (auto& r : pricedRequests)
         {
            if (r.first[depth] == -1 || r.first[depth] == a)
               matchingReqs.push_back(r);
         }

         auto res = maxAmountRec(matchingReqs, depth + 1);
         if (a == -1) //For addresses only covered by a "*", compound by their number
            res *= (1001 - addrParts.size());
         amount += res;
      }
      return amount;
   }

   long long IPv444::maxAmount(std::vector<std::string> const& requests, std::vector<int> const& prices)
   {
      std::vector<AddrPrice> pricedRequests;
      for (size_t i = 0; i < requests.size(); ++i)
         pricedRequests.emplace_back(parseAddress(requests[i]), prices[i]);

      return maxAmountRec(pricedRequests, 0);
   }

   //--------------------------------------------------------------------------
   // AB
   //--------------------------------------------------------------------------

   std::string AB::createString(size_t size, size_t expectedPairCount)
   {
      for (size_t nbA = 1; nbA < size; ++nbA)
      {
         auto result = std::string(size - nbA, 'B') + std::string(nbA, 'A');

         size_t pairCount = 0;
         while (pairCount < expectedPairCount)
         {
            auto i = result.find("BA");
            if (i == std::string::npos)
               break;

            std::swap(result[i], result[i + 1]);
            ++pairCount;
         }

         if (pairCount == expectedPairCount)
            return result;
      }

      return "";
   }


   //--------------------------------------------------------------------------
   // ABC
   //--------------------------------------------------------------------------

   struct AbcString
   {
      AbcString(size_t size, size_t expectedCount)
         : m_result(size, 'A')
         , m_expectedCount(expectedCount)
      {}
      
      std::string m_result;
      size_t m_expectedCount;

      bool create(size_t index, size_t nbA, size_t nbB, size_t currentCount)
      {
         if (currentCount == m_expectedCount) return true;
         if (index == m_result.size() || currentCount > m_expectedCount) return false;

         m_result[index] = 'A';
         if (create(index + 1, nbA + 1, nbB, currentCount))
            return true;

         m_result[index] = 'B';
         if (create(index + 1, nbA, nbB + 1, currentCount + nbA))
            return true;

         m_result[index] = 'C';
         if (create(index + 1, nbA, nbB, currentCount + nbA + nbB))
            return true;

         return false;
      }
   };

   std::string ABC::createString(size_t size, size_t expectedPairCount)
   {
      AbcString abcString(size, expectedPairCount);
      if (abcString.create(0, 0, 0, 0))
         return abcString.m_result;
      return "";
   }
}
