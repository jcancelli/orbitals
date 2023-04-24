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
    result[i] += vector.dot(matrix[i]);
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T, class Scalar,
          class = std::enable_if_t<std::is_arithmetic_v<Scalar>>>
inline mat<tRows, tCols, T> operator*(mat<tRows, tCols, T> const& matrix, Scalar scalar) {
  mat<tRows, tCols, T> result;
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      result[i][j] = matrix[i][j] * scalar;
    }
  }
  return result;
}

template <std::size_t tRows, std::size_t tCols, class T, class Scalar,
          class = std::enable_if_t<std::is_arithmetic_v<Scalar>>>
inline mat<tRows, tCols, T> operator*(Scalar scalar, mat<tRows, tCols, T> const& matrix) {
  mat<tRows, tCols, T> result;
  for (int i = 0; i < tCols; i++) {
    for (int j = 0; j < tRows; j++) {
      result[i][j] = matrix[i][j] * scalar;
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
T& mat<tRows, tCols, T>::operator()(std::size_t col, std::size_t row) {
  assert(col >= 0 && col < tCols && row >= 0 && row < tRows);
  return m_Value[col][row];
}

template <std::size_t tRows, std::size_t tCols, class T>
T const& mat<tRows, tCols, T>::operator()(std::size_t col, std::size_t row) const {
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

template <std::size_t tRows, std::size_t tCols, class T>
inline std::ostream& operator<<(std::ostream& os, mat<tRows, tCols, T> const& matrix) {
  os << "{";
  for (int row = 0; row < tRows; row++) {
    os << "{" << matrix[0][row];
    for (int col = 1; col < tCols; col++) {
      os << ", " << matrix[col][row];
    }
    os << "}";
  }
  os << "}";
  return os;
}

}  // namespace math

}  // namespace orbitals