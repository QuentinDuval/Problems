#pragma once


namespace prob
{
   template<typename Iterator>
   class Range
   {
   public:
      Range(Iterator first, Iterator last)
         : m_first(first), m_last(last) {}

      Iterator begin()  const { return m_first; }
      Iterator end()    const { return m_last; }

      size_t   size()   const { return std::distance(m_first, m_last); }
      bool     empty()  const { return m_first == m_last; }
      void     pop()          { ++m_first; }

   private:
      Iterator m_first;
      Iterator m_last;
   };

   template<typename Iterator>
   Range<Iterator> makeRange(Iterator first, Iterator last)
   {
      return Range<Iterator>(first, last);
   }
}
