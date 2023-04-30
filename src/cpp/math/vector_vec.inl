#pragma once

#include <boost/math/special_functions/rsqrt.hpp>

#include "vector.hpp"

namespace orbitals {

namespace math {

template <std::size_t vecSize, class T>
vec<vecSize, T>::vec() {
  m_Value.fill(0);
}

template <std::size_t vecSize, class T>
vec<vecSize, T>::vec(T initialValue) {
  for (int i = 0; i < vecSize; i++) {
    m_Value[i] = initialValue;
  }
}

template <std::size_t vecSize, class T>
vec<vecSize, T>::vec(vec<vecSize, T> const& other) {
  for (int i = 0; i < vecSize; i++) {
    m_Value[i] = other[i];
  }
}

template <std::size_t vecSize, class T>
vec<vecSize, T> vec<vecSize, T>::operator+(vec<vecSize, T> const& other) const {
  vec<vecSize, T> result;
  for (int i = 0; i < vecSize; i++) {
    result[i] = m_Value[i] + other[i];
  }
  return result;
}

template <std::size_t vecSize, class T>
vec<vecSize, T> vec<vecSize, T>::operator-(vec<vecSize, T> const& other) const {
  vec<vecSize, T> result;
  for (int i = 0; i < vecSize; i++) {
    result[i] = m_Value[i] - other[i];
  }
  return result;
}

template <std::size_t vecSize, class T, class Scalar,
          class = std::enable_if_t<std::is_arithmetic_v<Scalar>>>
inline vec<vecSize, T> operator*(vec<vecSize, T> const& vector, Scalar scalar) {
  vec<vecSize, T> result;
  for (int i = 0; i < vecSize; i++) {
    result[i] = vector[i] * scalar;
  }
  return result;
}

template <std::size_t vecSize, class T, class Scalar,
          class = std::enable_if_t<std::is_arithmetic_v<Scalar>>>
inline vec<vecSize, T> operator*(Scalar scalar, vec<vecSize, T> const& vector) {
  vec<vecSize, T> result;
  for (int i = 0; i < vecSize; i++) {
    result[i] = vector[i] * scalar;
  }
  return result;
}

template <std::size_t vecSize, class T, class Scalar,
          class = std::enable_if_t<std::is_arithmetic_v<Scalar>>>
inline vec<vecSize, T> operator/(vec<vecSize, T> const& vector, Scalar scalar) {
  assert(scalar != 0);
  vec<vecSize, T> result;
  for (int i = 0; i < vecSize; i++) {
    result[i] = vector[i] / scalar;
  }
  return result;
}

template <std::size_t vecSize, class T>
vec<vecSize, T>& vec<vecSize, T>::operator=(vec<vecSize, T> const& other) {
  if (this != &other) {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] = other[i];
    }
  }
  return *this;
}

template <std::size_t vecSize, class T>
vec<vecSize, T>& vec<vecSize, T>::operator+=(vec<vecSize, T> const& other) {
  for (int i = 0; i < vecSize; i++) {
    m_Value[i] += other[i];
  }
  return *this;
}

template <std::size_t vecSize, class T>
vec<vecSize, T>& vec<vecSize, T>::operator-=(vec<vecSize, T> const& other) {
  for (int i = 0; i < vecSize; i++) {
    m_Value[i] -= other[i];
  }
  return *this;
}

template <std::size_t vecSize, class T>
template <class Scalar, class>
vec<vecSize, T>& vec<vecSize, T>::operator*=(Scalar scalar) {
  for (int i = 0; i < vecSize; i++) {
    m_Value[i] *= scalar;
  }
  return *this;
}

template <std::size_t vecSize, class T>
template <class Scalar, class>
vec<vecSize, T>& vec<vecSize, T>::operator/=(Scalar scalar) {
  assert(scalar != 0);
  for (int i = 0; i < vecSize; i++) {
    m_Value[i] /= scalar;
  }
  return *this;
}

template <std::size_t vecSize, class T>
bool vec<vecSize, T>::operator==(vec<vecSize, T> const& other) const {
  for (int i = 0; i < vecSize; i++) {
    if (m_Value[i] != other[i]) {
      return false;
    }
  }
  return true;
}

template <std::size_t vecSize, class T>
bool vec<vecSize, T>::operator!=(vec<vecSize, T> const& other) const {
  for (int i = 0; i < vecSize; i++) {
    if (m_Value[i] == other[i]) {
      return false;
    }
  }
  return true;
}

template <std::size_t vecSize, class T>
T& vec<vecSize, T>::operator[](std::size_t i) {
  assert(i >= 0 && i < vecSize);
  return m_Value[i];
}

template <std::size_t vecSize, class T>
T const& vec<vecSize, T>::operator[](std::size_t i) const {
  assert(i >= 0 && i < vecSize);
  return m_Value[i];
}

template <std::size_t vecSize, class T>
T const* vec<vecSize, T>::data() const {
  return &m_Value[0];
}

template <std::size_t vecSize, class T>
T* vec<vecSize, T>::data() {
  return &m_Value[0];
}

template <std::size_t vecSize, class T>
inline std::ostream& operator<<(std::ostream& os, vec<vecSize, T> const& vector) {
  os << "{ " << vector[0];
  for (int i = 1; i < vecSize; i++) {
    os << ", " << vector[i];
  }
  os << " }";
  return os;
}

template <std::size_t vecSize, class T>
T vec<vecSize, T>::dot(vec<vecSize, T> const& other) const {
  T result = 0;
  for (int i = 0; i < vecSize; i++) {
    result += m_Value[i] * other[i];
  }
  return result;
}

template <std::size_t vecSize, class T>
vec<vecSize, T>& vec<vecSize, T>::normalize() {
  *this *= boost::math::rsqrt(this->dot(*this));
  return *this;
}

template <std::size_t vecSize, class T>
vec<vecSize, T> vec<vecSize, T>::normalized() const {
  return vec<vecSize, T>(*this).normalize();
}

template <std::size_t vecSize, class T>
float vec<vecSize, T>::length() const {
  return std::sqrt(this->dot(*this));
}

template <std::size_t vecSize, class T>
float vec<vecSize, T>::distance(vec<vecSize, T> const& other) const {
  return (*this - other).length();
}

template <std::size_t vecSize, class T>
vec<vecSize, T> vec<vecSize, T>::reflected(vec<vecSize, T> const& surfOrient) const {
  return *this - surfOrient * surfOrient.dot(*this) * static_cast<T>(2);
}

template <std::size_t vecSize, class T>
vec<vecSize, T> vec<vecSize, T>::refracted(vec<vecSize, T> const& surfNormal,
                                           T refrIndicesRatio) const {
  T const dotValue(surfNormal.dot(*this));
  T const k(static_cast<T>(1) -
            refrIndicesRatio * refrIndicesRatio * (static_cast<T>(1) - dotValue * dotValue));
  return (k >= static_cast<T>(0)) ? (refrIndicesRatio * (*this) -
                                     (refrIndicesRatio * dotValue + std::sqrt(k)) * surfNormal)
                                  : vec<vecSize, T>(0);
}

template <std::size_t vecSize, class T>
constexpr std::size_t vec<vecSize, T>::size() const {
  return vecSize;
}

}  // namespace math

}  // namespace orbitals