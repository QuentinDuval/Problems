#pragma once
#include "utils/Algorithms.h"

#include <vector>


namespace prob
{
   template<typename T>
   class Matrix
   {
   public:
      Matrix(size_t w, size_t h, T const& val)
         : m_width(w)
         , m_height(h)
         , m_data(w * h, val)
      {}

      Matrix(size_t w, size_t h, std::initializer_list<T> const& init)
         : Matrix(w, h)
      {
         size_t i = 0;
         for (auto d : init)
         {
            at(i % m_width, i / m_width) = d;
            ++i;
         }
      }

      Matrix(size_t w, size_t h) : Matrix(w, h, T()) {}
      ~Matrix() = default;

      size_t width()  const { return m_width; }
      size_t height() const { return m_height; }

      T&       at(size_t x, size_t y)        { return m_data[x + m_width * y]; }
      T const& at(size_t x, size_t y) const  { return m_data[x + m_width * y]; }

      friend bool operator== (Matrix<T> const& lhs, Matrix<T> const& rhs)
      {
         return equal(lhs.m_data, rhs.m_data);
      }

      void swap(Matrix<T>& other)
      {
         std::swap(other.m_width, m_width);
         std::swap(other.m_height, m_height);
         std::swap(other.m_data, m_data);
      }

   private:
      size_t m_width;
      size_t m_height;
      std::vector<T> m_data;
   };
}
