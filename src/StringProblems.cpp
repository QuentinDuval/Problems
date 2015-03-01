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
   // SUB STRING SEARCH
   //--------------------------------------------------------------------------

   std::string::size_type SubStringSearch::boyerMooreSearch(std::string const& text, std::string const& pattern)
   {
      if (pattern.empty() || text.empty())
         return std::string::npos;

      int tLen = text.size();
      int pLen = pattern.size();

      std::vector<int> lastOccur(UCHAR_MAX + 1, -1);
      for (int i = 0; i < pLen; ++i)
         lastOccur[pattern[i] - CHAR_MIN] = i;

      for (int start = 0; start < tLen - pLen + 1;)
      {
         int j = pLen - 1;
         for (; 0 <= pLen; --j)
         {
            if (pattern[j] != text[start + j])
               break;
            if (j == 0)
               return start;
         }

         int offset = pLen - lastOccur[pattern[j] - CHAR_MIN];
         start += offset;
      }

      return std::string::npos;
   }

   std::string::size_type SubStringSearch::kmpSearch(std::string const& text, std::string const& pattern)
   {
      if (pattern.empty() || text.empty())
         return std::string::npos;

      int tLen = text.size();
      int pLen = pattern.size();
      int radix = UCHAR_MAX + 1;

      std::vector<int> nextState(radix * (pLen + 1), 0);
      nextState[pattern[0] - CHAR_MIN] = 1;

      int fail = 0;
      for (int curr = 1; curr <= pLen; ++curr)
      {
         for (int c = 0; c < radix; ++c)
         {
            //Go to the state to which we would have had to backtracked
            //Re-read the start of the pattern + the new character
            nextState.at(c + curr * radix) = nextState.at(c + fail * radix);
         }

         int c = pattern[curr] - CHAR_MIN;
         nextState.at(c + curr * radix) = curr + 1;

         //Fail state is the state to which we would have been if we had backtracked
         //Reading the [1..curr] first caracters of the pattern
         fail = nextState.at(c + fail * radix);
      }

      //Represents the number of char matched
      int state = 0; 
      for (int i = 0; i < tLen; ++i)
      {
         char c = text[i];
         state = nextState.at(c - CHAR_MIN + state * radix);
         if (state == pLen)
            return i - pLen + 1;

      }
      return std::string::npos;
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


   //--------------------------------------------------------------------------
   // DECIPHERABILITY
   //--------------------------------------------------------------------------

   bool Decipherability::check(std::string const& input, int removedNb)
   {
      if (input.size() == removedNb)
         return true;

      std::vector<int> lastIndices(UCHAR_MAX + 1, - (removedNb + 1));
      for (size_t i = 0; i < input.size(); ++i)
      {
         char c = input[i];
         if (i - lastIndices[c] <= removedNb)
            return false;

         lastIndices[c] = i;
      }
      return true;
   }

   //--------------------------------------------------------------------------
   // TaroFillingAStringDiv1
   //--------------------------------------------------------------------------
   
   /** 
    * OBSERVATIONS:
    *
    * If the gap between 2 chosen letters is:
    * - pair between different letters => 1 way not to increase
    * - impair between similar letters => 1 way not to increase
    *
    * - impair between different letters:
    *    A?B => 2 choices
    *    A???B => 4 choices (ABA, BAA, BAB, BBA)
    *    A?{2*N+1}?B
    *       => A..A * {impair similar letter = 1}
    *       => B..B * {impair similar letter = 1}
    *       => B..A * {impair different letter = recursion}
    *    
    * - pair between similar letters:
    *    A??A => 3 choices (AB, BA, BB)
    *    A?{2*N}?A
    *       => A..B * {different letters 2N = 1}
    *       => B..A * {different letters 2N = 1}
    *       => B..B * {similar letters 2N = recursion}
    *
    * Both look like:
    * F(GapSize) = 2 + F(GapSize - 2) with F(1) = 2 and F(0) = 1
    */

   static int possibilities(int n)
   {
      if (n == 0) return 1;
      if (n == 1) return 2;
      return 2 + possibilities(n - 2);
   }

   int TaroFillingAStringDiv1::getNumber(int size, std::vector<int> const& positions, std::string const& values)
   {
      //Start by sorting the inputs (and moving back to 0-based index)
      std::vector<std::pair<int, char>> knownPositions;
      zipWith(positions, values, std::back_inserter(knownPositions), [](int i, char c) { return std::make_pair(i - 1, c); });
      sortBy(knownPositions, comparingWith(GetFirst()));

      //What is before and after, known positions does not increase (we can always find a unique solution)
      int n = 1;
      for (size_t k = 1; k < knownPositions.size(); ++k)
      {
         auto gapStart = knownPositions[k - 1];
         auto gapEnd = knownPositions[k];
         bool differentBorder = gapEnd.second != gapStart.second;
         if (gapStart.first + 1 == gapEnd.first)
            continue;
         
         int gapSize = gapEnd.first - gapStart.first - 1;
         bool impairGap = gapSize % 2;

         if ((differentBorder && impairGap) || (!differentBorder && !impairGap))
         {
            int possiblities = possibilities(gapSize);
            n = (n % MOD) * (possiblities % MOD);
         }
      }

      return n;
   }


   //--------------------------------------------------------------------------
   // INTERNET SECURITY
   //--------------------------------------------------------------------------

   InternetSecurity::Keywords split(std::string const& s)
   {
      InternetSecurity::Keywords keywords(1, "");
      for (char c : s)
      {
         if (c == ' ') keywords.emplace_back();
         else keywords.back() += c;
      }
      return keywords;
   }

   size_t intersection(InternetSecurity::Keywords const& s1, InternetSecurity::Keywords const& s2)
   {
      //Better idea would be to sort one collection to do binary searches in it
      size_t count = 0;
      for (size_t i = 0; i < s1.size(); ++i)
      {
         auto it = std::find(begin(s2), end(s2), s1[i]);
         if (it != end(s2)) ++count;
      }
      return count;
   }

   InternetSecurity::Addresses InternetSecurity::determineWebsite(Addresses const& addresses, Keywords const& keywords, Keywords const& dangerous, int threshold)
   {
      //Group the sites with their associated keywords
      std::vector<bool> markedDangerous(addresses.size(), false);
      std::vector<Keywords> sitesKeywords(keywords.size());
      std::transform(begin(keywords), end(keywords), begin(sitesKeywords), split);

      //While there are some changes
      Keywords dangerousKeywords = dangerous;
      while (true)
      {
         bool additionalSite = false;
         for (size_t site = 0; site < addresses.size(); ++site)
         {
            if (markedDangerous[site])
               continue;

            if (threshold <= intersection(sitesKeywords[site], dangerousKeywords))
            {
               additionalSite = true;
               markedDangerous[site] = true;
               for (auto& k : sitesKeywords[site])
                  dangerousKeywords.push_back(k);
            }
         }
         if (!additionalSite)
            break;
      }

      //Contruct the result
      Keywords output;
      for (size_t site = 0; site < addresses.size(); ++site)
      {
         if (markedDangerous[site])
            output.push_back(addresses[site]);
      }
      return output;
   }


   //--------------------------------------------------------------------------
   // KING SORT
   //--------------------------------------------------------------------------

   static int romanNumberToInt(std::string const& romanNb)
   {
      int value = 0;
      if (romanNb.empty())
         return value;

      char prev = ' ';
      for (size_t i = 0; i < romanNb.size(); ++i)
      {
         char curr = romanNb[i];
         if (curr == 'I') value += 1;
         else if (curr == 'V') value += (prev == 'I') ? 3 : 5;
         else if (curr == 'X') value += (prev == 'I') ? 8 : 10;
         else if (curr == 'L') value += (prev == 'X') ? 30 : 50;
         prev = curr;
      }
      return value;
   }

   class King
   {
   public:
      King() = default;
      King(std::string const& fullName)
         : m_fullName(fullName)
      {
         auto index = m_fullName.find(' ');
         m_name = std::string(m_fullName, 0, index);
         std::string nbStr(m_fullName, index + 1);
         m_number = romanNumberToInt(nbStr);
      }

      std::string const& getFullName() const
      {
         return m_fullName;
      }

      friend bool operator< (King const& lhs, King const& rhs)
      {
         if (lhs.m_name != rhs.m_name) return lhs.m_name < rhs.m_name;
         return lhs.m_number < rhs.m_number;
      }

   private:
      std::string m_fullName;
      std::string m_name;
      int m_number;
   };

   KingSort::KingNames KingSort::getSortedList(KingNames const& kingFullNames)
   {
      std::vector<King> kings(kingFullNames.size());
      std::copy(begin(kingFullNames), end(kingFullNames), begin(kings));
      std::sort(begin(kings), end(kings));

      KingSort::KingNames orderedFullNames(kingFullNames.size());
      std::transform(begin(kings), end(kings), begin(orderedFullNames), [](King const& k) { return k.getFullName(); });
      return orderedFullNames;
   }


   //--------------------------------------------------------------------------
   // BUS AWAITING
   //--------------------------------------------------------------------------

   struct BusTiming
   {
      BusTiming() = default;
      BusTiming(std::string const& b)
      {
         auto sep1 = b.find(' ');
         auto sep2 = b.find(' ', sep1 + 1);
         m_arrival = atoi(std::string(b, 0, sep1).c_str());
         m_interval = atoi(std::string(b, sep1, sep2).c_str());
         m_count = atoi(std::string(b, sep2).c_str());
      }

      int m_arrival;
      int m_interval;
      int m_count;
   };

   int BusAwaiting::waitingTime(std::vector<std::string> const& buses, int arrivalTime)
   {
      std::vector<BusTiming> timings(buses.size());
      std::copy(begin(buses), end(buses), begin(timings));

      int waitingTime = -1;
      for (auto& timing : timings)
      {
         for (int c = 0; c < timing.m_count; ++c)
         {
            int nextArrival = timing.m_arrival + timing.m_interval * c;
            if (nextArrival < arrivalTime)
               continue;
            
            int wait = nextArrival - arrivalTime;
            if (waitingTime < 0) waitingTime = wait;
            else waitingTime = std::min(waitingTime, wait);
         }
      }
      return waitingTime;
   }


   //--------------------------------------------------------------------------
   // SEARCH DISKS
   //--------------------------------------------------------------------------

   int SearchDisks::numberToTakeOut(std::string const& diskNames, std::string const& searchingDisk)
   {
      std::vector<std::string> disks(1, "");
      for (char c : diskNames)
      {
         if (c != ' ') disks.back() += c;
         else disks.emplace_back();
      }

      int count = 0;
      while (!disks.empty())
      {
         if (disks.back() == searchingDisk)
            return count;

         disks.pop_back();
         ++count;
      }
      return -1;
   }


   //--------------------------------------------------------------------------
   // TEMPLATE MATCHING
   //--------------------------------------------------------------------------

   static int getSuffixScore(std::string const& text, std::string const& suffix)
   {
      int count = 0;
      for (int c = 0; c < text.size(); ++c)
      {
         int len = text.size() - c;
         std::string textEnd = text.substr(c, std::string::npos);
         std::string sufStart = suffix.substr(0, len);
         if (textEnd == sufStart)
            return len;
      }
      return 0;
   }

   std::string TemplateMatching::bestMatch(std::string const& text, std::string const& prefix, std::string const& suffix)
   {
      int bestScore = 0;
      int bestPrefix = 0;
      std::string bestMatch;

      for (int len = 1; len <= text.size(); ++len)
      {
         for (int start = 0; start < text.size() - len + 1; ++start)
         {
            std::string subText = text.substr(start, len);
            int prefixScore = getSuffixScore(prefix, subText);
            int suffixScore = getSuffixScore(subText, suffix);
            int newScore = prefixScore + suffixScore;

            if (bestScore < newScore)
            {
               bestScore = newScore;
               bestPrefix = prefixScore;
               bestMatch = subText;
            }
            else if (bestScore == newScore)
            {
               if (prefixScore > bestPrefix)
               {
                  bestPrefix = prefixScore;
                  bestMatch = subText;
               }
               else if (bestMatch.empty() || bestMatch > subText)
               {
                  bestMatch = subText;
               }
            }
         }
      }
      return bestMatch;
   }


   //--------------------------------------------------------------------------
   // SORT BOOKS
   //--------------------------------------------------------------------------

   std::vector<size_t> SortBooks::checkManually(std::vector<std::string> const& firstFields, std::vector<std::string> const& secondFields)
   {
      std::vector<size_t> ambigious;
      for (size_t i = 0; i < firstFields.size(); ++i)
      {
         bool is1Title = qualifyAsTitle(firstFields[i]);
         bool is2Title = qualifyAsTitle(secondFields[i]);
         if (is1Title == is2Title)
            ambigious.push_back(i);
      }
      return ambigious;
   }

   static bool equalNoCase(std::string const& lhs, std::string const& rhs)
   {
      if (lhs.size() != rhs.size()) return false;
      return std::equal(begin(lhs), end(lhs), begin(rhs),
         [](char l, char r) { return ::tolower(l) == ::tolower(r); });
   }

   bool SortBooks::qualifyAsTitle(std::string const& field)
   {
      std::vector<std::string> words = splitWords(field);
      if (3 < words.size())
         return true;

      static std::vector<std::string> searched = { "the", "and", "of" };
      for (auto& w : words)
      {
         auto it = std::find_if(begin(searched), end(searched), [&](std::string const& s) { return equalNoCase(w, s); });
         if (end(searched) != it)
            return true;
      }
      return false;
   }

   std::vector<std::string> SortBooks::splitWords(std::string const& s)
   {
      std::vector<std::string> words(1, "");
      for (size_t i = 0; i < s.size(); ++i)
      {
         if (s.at(i) == ' ') words.emplace_back();
         else words.back().push_back(s.at(i));
      }
      auto last = std::remove_if(begin(words), end(words), [](std::string const& s){ return s.empty(); });
      words.erase(last, end(words));
      return words;
   }


   //--------------------------------------------------------------------------
   // SERIAL NUMBERS
   //--------------------------------------------------------------------------

   static int sumDigits(std::string const& s)
   {
      int sum = 0;
      for (char c : s)
      {
         if (::isdigit(c))
            sum += c - '0';
      }
      return sum;
   }

   std::vector<std::string> SerialNumbers::sortSerials(std::vector<std::string> const& serialNbs)
   {
      std::vector<std::string> sorted(serialNbs);
      std::sort(begin(sorted), end(sorted));
      std::stable_sort(begin(sorted), end(sorted), comparingWith(sumDigits));
      std::stable_sort(begin(sorted), end(sorted), comparingWith([](std::string const& s) { return s.size(); }));
      return sorted;
   }


   //--------------------------------------------------------------------------
   // TOURNAMENTS AMBIGUITY NUMBER
   //--------------------------------------------------------------------------

   int countWinCycle(std::vector<std::string> const& table, int winner, int looser)
   {
      int count = 0;
      for (int p = 0; p < table.size(); ++p)
      {
         if (winner == p || looser == p)
            continue;

         if ((table[looser][p] == '1') && (table[p][winner] == '1'))
            ++count;
      }
      return count;
   }

   int TournamentsAmbiguityNumber::scrutinizeTable(std::vector<std::string> const& table)
   {
      int ambiguityCount = 0;
      for (int p1 = 0; p1 < table.size(); ++p1)
      {
         for (int p2 = p1 + 1; p2 < table.size(); ++p2)
         {
            if (table[p1][p2] == '1')
               ambiguityCount += countWinCycle(table, p1, p2);
            else if (table[p1][p2] == '0')
               ambiguityCount += countWinCycle(table, p2, p1);
         }
      }
      return ambiguityCount;
   }


   //--------------------------------------------------------------------------
   // JOSH STRING
   //--------------------------------------------------------------------------

   static bool isPrime(int n)
   {
      int max = static_cast<int>(sqrt(n)) + 1;
      for (int i = 2; i <= max; ++i)
      {
         if (n % i == 0)
            return false;
      }
      return true;
   }

   bool JoshString::isJoshString(std::string const& str)
   {
      int sumLetters = 0;
      for (char c : str)
      {
         sumLetters += c - 'a' + 1;
      }
      return isPrime(sumLetters);
   }


   //--------------------------------------------------------------------------
   // QUOTE CONTEST
   //--------------------------------------------------------------------------

   std::pair<int, std::string> splitVote(std::string const& str)
   {
      auto space1 = str.find(' ');
      auto space2 = str.find(' ', space1 + 1);
      auto vote1 = str.substr(0, space1);
      auto vote2 = str.substr(space1 + 1, space2 - space1 - 1);

      int count = atoi(vote1.c_str()) + atoi(vote2.c_str());
      return std::make_pair(count, str.substr(space2 + 1));
   }

   std::string QuoteContest::bestQuote(std::vector<std::string> const& quotes)
   {
      std::vector<std::pair<int, std::string>> votes(quotes.size());
      std::transform(begin(quotes), end(quotes), begin(votes), splitVote);
      auto maxIt = std::max_element(begin(votes), end(votes), comparingWith(GetFirst()));
      return maxIt != end(votes) ? maxIt->second : "";
   }
}
