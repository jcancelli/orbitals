#pragma once

#include "matrix.hpp"

namespace orbitals {

namespace math {

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T>::mat() {
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T>::mat(mat<tRows, tCols, T> const& other) {
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      m_Value[i][j] = other[i][j];
    }
  }
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T> mat<tRows, tCols, T>::operator+(mat<tRows, tCols, T> const& other) const {
  mat<tRows, tCols, T> result;
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      result[i][j] = m_Value[i][j] + other[i][j];
    }
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T> mat<tRows, tCols, T>::operator-(mat<tRows, tCols, T> const& other) const {
  mat<tRows, tCols, T> result;
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      result[i][j] = m_Value[i][j] - other[i][j];
    }
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T>
template <std::size_t otherCols>
mat<tRows, otherCols, T> mat<tRows, tCols, T>::operator*(
    mat<tCols, otherCols, T> const& other) const {
  mat<tRows, otherCols, T> result;
  for (int i = 0; i < tRows; i++) {
    for (int j = 0; j < otherCols; j++) {
      for (int k = 0; k < tCols; k++) {
        result[j][i] += m_Value[k][i] * other[j][k];
      }
    }
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T>
inline vec<tRows, T> operator*(mat<tRows, tCols, T> const& matrix, vec<tCols, T> const& vector) {
  vec<tRows, T> result;
  for (int i = 0; i < tRows; i++) {
    for (int j = 0; j < tCols; j++) {
      result[i] += matrix[j][i] * vector[j];
    }
  }
  return result;
}

template <std::size_t vecSize, std::size_t matCols, class T>
inline vec<matCols, T> operator*(vec<vecSize, T> const& vector,
                                 mat<vecSize, matCols, T> const& matrix) {
  vec<matCols, T> result;
  for (int i = 0; i < matCols; i++) {
    result[i] += vector * matrix[i];
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T> mat<tRows, tCols, T>::operator*(T scalar) const {
  mat<tRows, tCols, T> result;
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      result[i][j] = m_Value[i][j] * scalar;
    }
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T>& mat<tRows, tCols, T>::operator=(mat<tRows, tCols, T> const& other) {
  if (this != &other) {
    for (int i = 0; i < tCols; i++) {
      for (int j = 0; j < tRows; j++) {
        m_Value[i][j] = other[i][j];
      }
    }
  }
  return *this;
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T>& mat<tRows, tCols, T>::operator+=(mat<tRows, tCols, T> const& other) {
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      m_Value[i][j] += other[i][j];
    }
  }
  return *this;
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T>& mat<tRows, tCols, T>::operator-=(mat<tRows, tCols, T> const& other) {
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      m_Value[i][j] -= other[i][j];
    }
  }
  return *this;
}

template <std::size_t tRows, std::size_t tCols, class T>
mat<tRows, tCols, T> mat<tRows, tCols, T>::operator*=(T scalar) {
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      m_Value[i][j] *= scalar;
    }
  }
  return *this;
}

template <std::size_t tRows, std::size_t tCols, class T>
bool mat<tRows, tCols, T>::operator==(mat<tRows, tCols, T> const& other) const {
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      if (m_Value[i][j] != other[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <std::size_t tRows, std::size_t tCols, class T>
bool mat<tRows, tCols, T>::operator!=(mat<tRows, tCols, T> const& other) const {
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      if (m_Value[i][j] == other[i][j]) {
        return false;
      }
    }
  }
  return true;
}

template <std::size_t tRows, std::size_t tCols, class T>
vec<tRows, T>& mat<tRows, tCols, T>::operator[](std::size_t col) {
  assert(col >= 0 && col < tCols);
  return m_Value[col];
}

template <std::size_t tRows, std::size_t tCols, class T>
vec<tRows, T> const& mat<tRows, tCols, T>::operator[](std::size_t col) const {
  assert(col >= 0 && col < tCols);
  return m_Value[col];
}

template <std::size_t tRows, std::size_t tCols, class T>
vec<tRows, T>& mat<tRows, tCols, T>::operator()(std::size_t col, std::size_t row) {
  assert(col >= 0 && col < tCols && row >= 0 && row < tRows);
  return m_Value[col][row];
}

template <std::size_t tRows, std::size_t tCols, class T>
vec<tRows, T> const& mat<tRows, tCols, T>::operator()(std::size_t col, std::size_t row) const {
  assert(col >= 0 && col < tCols && row >= 0 && row < tRows);
  return m_Value[col][row];
}

template <std::size_t tRows, std::size_t tCols, class T>
T const* mat<tRows, tCols, T>::data() const {
  return m_Value[0].data();
}

template <std::size_t tRows, std::size_t tCols, class T>
T* mat<tRows, tCols, T>::data() {
  return m_Value[0].data();
}

template <std::size_t tRows, std::size_t tCols, class T>
constexpr std::size_t mat<tRows, tCols, T>::rows() const {
  return tRows;
}

template <std::size_t tRows, std::size_t tCols, class T>
constexpr std::size_t mat<tRows, tCols, T>::columns() const {
  return tCols;
}

template <std::size_t tSize, class T>
generic_square_mat<tSize, T>::generic_square_mat(T identityValue) {
  for (int i = 0; i < tSize; i++) {
    (*this)[i][i] = identityValue;
  }
}

// template <std::size_t tSize, class T>
// generic_square_mat<tSize, T>& generic_square_mat<tSize, T>::operator=(
//     generic_square_mat<tSize, T> const& other) {
//   return mat<tSize, tSize, T>::operator=(other);
// }

template <class T>
generic_mat4<T>::generic_mat4() {
}

template <class T>
generic_mat4<T>::generic_mat4(T identityValue)
    : generic_square_mat<4, T>::generic_square_mat(identityValue) {
}

template <class T>
generic_mat4<T>::generic_mat4(mat<4, 4, T> const& other)
    : generic_square_mat<4, T>::generic_square_mat(other) {
}

template <class T>
generic_mat4<T>& generic_mat4<T>::translate(float x, float y, float z) {
  generic_mat4<T>& m = *this;
  m[3] = m[0] * x + m[1] * y + m[2] * z + m[3];
  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::translate(vec<3, T> const& amount) {
  return translate(amount.x, amount.y, amount.z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::translated(vec<3, T> const& amount) const {
  return generic_mat4<T>(*this).translate(amount);
}

template <class T>
generic_mat4<T> generic_mat4<T>::rotate(T angle, generic_vec3<T> const& rotationAxis) {
  T const c = std::cos(angle);
  T const s = std::sin(angle);

  generic_vec3<T> axis(rotationAxis.normalized());
  generic_vec3<T> temp((T(1) - c) * axis);
  generic_mat4<T> rotation;

  rotation[0][0] = c + temp[0] * axis[0];
  rotation[0][1] = temp[0] * axis[1] + s * axis[2];
  rotation[0][2] = temp[0] * axis[2] - s * axis[1];

  rotation[1][0] = temp[1] * axis[0] - s * axis[2];
  rotation[1][1] = c + temp[1] * axis[1];
  rotation[1][2] = temp[1] * axis[2] + s * axis[0];

  rotation[2][0] = temp[2] * axis[0] + s * axis[1];
  rotation[2][1] = temp[2] * axis[1] - s * axis[0];
  rotation[2][2] = c + temp[2] * axis[2];

  generic_mat4<T>& m(*this);
  generic_mat4<T>& result = *this;

  result[0] = m[0] * rotation[0][0] + m[1] * rotation[0][1] + m[2] * rotation[0][2];
  result[1] = m[0] * rotation[1][0] + m[1] * rotation[1][1] + m[2] * rotation[1][2];
  result[2] = m[0] * rotation[2][0] + m[1] * rotation[2][1] + m[2] * rotation[2][2];
  result[3] = m[3];

  return *this;
}

template <class T>
generic_mat4<T> generic_mat4<T>::rotated(T angle, vec<3, T> const& rotationAxis) const {
  return generic_mat4<T>(*this).rotate(angle, rotationAxis);
}

template <class T>
generic_mat4<T>& generic_mat4<T>::scale(float x, float y, float z) {
  generic_mat4<T> m(*this);
  generic_mat4<T>& result = *this;

  result[0] = m[0] * x;
  result[1] = m[1] * y;
  result[2] = m[2] * z;
  result[3] = m[3];

  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::scale(vec<3, T> const& amount) {
  return scale(amount.x, amount.y, amount.z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::scaled(float x, float y, float z) const {
  return generic_mat4<T>(*this).scale(x, y, z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::scaled(vec<3, T> const& amount) const {
  return generic_mat4<T>(*this).scale(amount);
}

// template <class T>
// generic_mat4<T>& generic_mat4<T>::operator=(generic_mat4<T> const& other) {
//   return generic_square_mat<4, T>::operator=(other);
// }

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