#pragma once

#include <array>
#include <cassert>
#include <type_traits>

#include "vector.hpp"

namespace orbitals {

namespace math {

template <std::size_t tRows, std::size_t tCols, class T>
class mat {
  static_assert(tRows > 0);
  static_assert(tCols > 0);
  static_assert(std::is_arithmetic<T>::value);

 private:
  std::array<vec<tRows, T>, tCols> m_Value;  // column major

 public:
  mat();
  mat(mat<tRows, tCols, T> const& other);

  mat<tRows, tCols, T> operator+(mat<tRows, tCols, T> const& other) const;
  mat<tRows, tCols, T> operator-(mat<tRows, tCols, T> const& other) const;
  template <std::size_t otherCols>
  mat<tRows, otherCols, T> operator*(mat<tCols, otherCols, T> const& other) const;
  mat<tRows, tCols, T> operator*(T scalar) const;

  mat<tRows, tCols, T>& operator=(mat<tRows, tCols, T> const& other);
  mat<tRows, tCols, T>& operator+=(mat<tRows, tCols, T> const& other);
  mat<tRows, tCols, T>& operator-=(mat<tRows, tCols, T> const& other);
  mat<tRows, tCols, T> operator*=(T scalar);

  bool operator==(mat<tRows, tCols, T> const& other) const;
  bool operator!=(mat<tRows, tCols, T> const& other) const;

  vec<tRows, T>& operator[](std::size_t col);
  vec<tRows, T> const& operator[](std::size_t col) const;

  vec<tRows, T>& operator()(std::size_t col, std::size_t row);
  vec<tRows, T> const& operator()(std::size_t col, std::size_t row) const;

  T const* data() const;
  T* data();

  constexpr std::size_t rows() const;
  constexpr std::size_t columns() const;
};

template <std::size_t tRows, std::size_t tCols, class T>
inline vec<tRows, T> operator*(mat<tRows, tCols, T> const& matrix, vec<tCols, T> const& vector);
template <std::size_t vecSize, std::size_t matCols, class T>
inline vec<matCols, T> operator*(vec<vecSize, T> const& vector,
                                 mat<vecSize, matCols, T> const& matrix);

template <std::size_t tSize, class T>
class generic_square_mat : public mat<tSize, tSize, T> {
  static_assert(tSize > 0);
  static_assert(std::is_arithmetic<T>::value);

 public:
  generic_square_mat(T identityValue);

  generic_square_mat<tSize, T>& operator=(generic_square_mat<tSize, T> const& other);
};

template <class T>
class generic_mat4 : public generic_square_mat<4, T> {
 public:
  generic_mat4();
  generic_mat4(T identityValue);
  generic_mat4(mat<4, 4, T> const& other);

  generic_mat4<T>& translate(float x, float y, float z);
  generic_mat4<T>& translate(vec<3, T> const& amount);
  generic_mat4<T> translated(vec<3, T> const& amount) const;
  generic_mat4<T> rotate(T angle, generic_vec3<T> const& rotationAxis);
  generic_mat4<T> rotated(T angle, vec<3, T> const& rotationAxis) const;
  generic_mat4<T>& scale(float x, float y, float z);
  generic_mat4<T>& scale(vec<3, T> const& amount);
  generic_mat4<T> scaled(float x, float y, float z) const;
  generic_mat4<T> scaled(vec<3, T> const& amount) const;
  generic_mat4<T>& operator=(generic_mat4<T> const& other);
};

using mat2 = mat<2, 2, float>;
using mat3 = mat<3, 3, float>;
using mat4 = generic_mat4<float>;
using imat2 = mat<2, 2, int>;
using imat3 = mat<3, 3, int>;
using imat4 = generic_mat4<int>;
using uimat2 = mat<2, 2, unsigned int>;
using uimat3 = mat<3, 3, unsigned int>;
using uimat4 = generic_mat4<unsigned int>;

}  // namespace math

}  // namespace orbitals

#include "matrix.inl"