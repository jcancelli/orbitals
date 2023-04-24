#pragma once

#include "vector.hpp"

namespace orbitals {

namespace math {

template <class T>
generic_vec4<T>::generic_vec4() {
}

template <class T>
generic_vec4<T>::generic_vec4(T x, T y, T z, T w) {
  this->x() = x;
  this->y() = y;
  this->z() = z;
  this->w() = w;
}

template <class T>
generic_vec4<T>::generic_vec4(T initialValue) : vec<4, T>(initialValue) {
}

template <class T>
generic_vec4<T>::generic_vec4(vec<4, T> const& other) : vec<4, T>(other) {
}

template <class T>
generic_vec4<T>& generic_vec4<T>::operator=(vec<4, T> const& other) {
  return vec<4, T>::operator=(other);
}

template <class T>
generic_vec4<T>& generic_vec4<T>::operator()(T x, T y, T z, T w) {
  this->x() = x;
  this->y() = y;
  this->z() = z;
  this->w() = w;
  return *this;
}

template <class T>
T& generic_vec4<T>::x() {
  return (*this)[0];
}

template <class T>
T const& generic_vec4<T>::x() const {
  return (*this)[0];
}

template <class T>
T& generic_vec4<T>::y() {
  return (*this)[1];
}

template <class T>
T const& generic_vec4<T>::y() const {
  return (*this)[1];
}

template <class T>
T& generic_vec4<T>::z() {
  return (*this)[2];
}

template <class T>
T const& generic_vec4<T>::z() const {
  return (*this)[2];
}

template <class T>
T& generic_vec4<T>::w() {
  return (*this)[3];
}

template <class T>
T const& generic_vec4<T>::w() const {
  return (*this)[3];
}
}  // namespace math

}  // namespace orbitals