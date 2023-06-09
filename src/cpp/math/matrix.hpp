#pragma once

#include <array>
#include <cassert>
#include <type_traits>

#include "quaternion.hpp"
#include "vector.hpp"

namespace orbitals {

namespace math {

template <std::size_t tRows, std::size_t tCols, class T>
class mat {
  static_assert(std::is_arithmetic_v<T>);

 private:
  std::array<vec<tRows, T>, tCols> m_Value;  // column major

 public:
  mat();
  mat(std::array<std::array<T, tRows>, tCols> values);  // input is row major for better readability
  mat(mat<tRows, tCols, T> const& other);

  mat<tRows, tCols, T> operator+(mat<tRows, tCols, T> const& other) const;
  mat<tRows, tCols, T> operator-(mat<tRows, tCols, T> const& other) const;

  template <std::size_t otherCols>
  mat<tRows, otherCols, T> operator*(mat<tCols, otherCols, T> const& other) const;

  mat<tRows, tCols, T>& operator=(mat<tRows, tCols, T> const& other);
  mat<tRows, tCols, T>& operator+=(mat<tRows, tCols, T> const& other);
  mat<tRows, tCols, T>& operator-=(mat<tRows, tCols, T> const& other);
  mat<tRows, tCols, T> operator*=(T scalar);

  bool operator==(mat<tRows, tCols, T> const& other) const;
  bool operator!=(mat<tRows, tCols, T> const& other) const;

  vec<tRows, T>& operator[](std::size_t col);
  vec<tRows, T> const& operator[](std::size_t col) const;

  T& operator()(std::size_t col, std::size_t row);
  T const& operator()(std::size_t col, std::size_t row) const;

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

template <std::size_t tRows, std::size_t tCols, class T, class Scalar, class>
inline mat<tRows, tCols, T> operator*(mat<tRows, tCols, T> const& matrix, Scalar scalar);
template <std::size_t tRows, std::size_t tCols, class T, class Scalar, class>
inline mat<tRows, tCols, T> operator*(Scalar scalar, mat<tRows, tCols, T> const& matrix);

template <std::size_t tRows, std::size_t tCols, class T>
inline std::ostream& operator<<(std::ostream& os, mat<tRows, tCols, T> const& matrix);

template <std::size_t tSize, class T>
class generic_square_mat : public mat<tSize, tSize, T> {
  static_assert(std::is_arithmetic_v<T>);

 public:
  generic_square_mat();
  generic_square_mat(T identityValue);
  generic_square_mat(std::array<std::array<T, tSize>, tSize> values);
  generic_square_mat(mat<tSize, tSize, T> const& other);

  mat<tSize, tSize, T>& operator=(mat<tSize, tSize, T> const& other);
};

template <class T>
class generic_mat4 : public generic_square_mat<4, T> {
 public:
  generic_mat4();
  generic_mat4(T identityValue);
  generic_mat4(std::array<std::array<T, 4>, 4> values);
  generic_mat4(mat<4, 4, T> const& other);
  generic_mat4(quat<T> const& quaternion);

  generic_mat4<T>& translate(float x, float y, float z);
  generic_mat4<T>& translate(generic_vec3<T> const& amount);
  generic_mat4<T> translated(float x, float y, float z) const;
  generic_mat4<T> translated(generic_vec3<T> const& amount) const;
  generic_mat4<T>& rotate(T angle, generic_vec3<T> const& rotationAxis);
  generic_mat4<T>& rotate(quat<T> const& quaternion);
  generic_mat4<T> rotated(T angle, generic_vec3<T> const& rotationAxis) const;
  generic_mat4<T> rotated(quat<T> const& quaternion) const;
  generic_mat4<T>& scale(float x, float y, float z);
  generic_mat4<T>& scale(generic_vec3<T> const& amount);
  generic_mat4<T> scaled(float x, float y, float z) const;
  generic_mat4<T> scaled(generic_vec3<T> const& amount) const;
  mat<4, 4, T>& operator=(mat<4, 4, T> const& other);
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

#include "matrix_generic_mat4.inl"
#include "matrix_generic_square_mat.inl"
#include "matrix_mat.inl"