#pragma once

#include "vector.hpp"

namespace orbitals {

namespace math {

template <class T>
generic_vec2<T>::generic_vec2() {
}

template <class T>
generic_vec2<T>::generic_vec2(T x, T y) {
  this->x() = x;
  this->y() = y;
}

template <class T>
generic_vec2<T>::generic_vec2(T initialValue) : vec<2, T>(initialValue) {
}

template <class T>
generic_vec2<T>::generic_vec2(vec<2, T> const& other) : vec<2, T>(other) {
}

template <class T>
generic_vec2<T>& generic_vec2<T>::operator=(vec<2, T> const& other) {
  return vec<2, T>::operator=(other);
}

template <class T>
generic_vec2<T>& generic_vec2<T>::operator()(T x, T y) {
  this->x() = x;
  this->y() = y;
  return *this;
}

template <class T>
T& generic_vec2<T>::x() {
  return (*this)[0];
}

template <class T>
T const& generic_vec2<T>::x() const {
  return (*this)[0];
}

template <class T>
T& generic_vec2<T>::y() {
  return (*this)[1];
}

template <class T>
T const& generic_vec2<T>::y() const {
  return (*this)[1];
}

}  // namespace math

}  // namespace orbitals