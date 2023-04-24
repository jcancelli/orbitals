#pragma once

#include "vector.hpp"

namespace orbitals {

namespace math {

template <class T>
generic_vec3<T>::generic_vec3() {
}

template <class T>
generic_vec3<T>::generic_vec3(T x, T y, T z) {
  this->x() = x;
  this->y() = y;
  this->z() = z;
}

template <class T>
generic_vec3<T>::generic_vec3(T initialValue) : vec<3, T>(initialValue) {
}

template <class T>
generic_vec3<T>::generic_vec3(vec<3, T> const& other) : vec<3, T>(other) {
}

template <class T>
generic_vec3<T>& generic_vec3<T>::operator=(vec<3, T> const& other) {
  return vec<3, T>::operator=(other);
}

template <class T>
generic_vec3<T>& generic_vec3<T>::operator()(T x, T y, T z) {
  this->x() = x;
  this->y() = y;
  this->z() = z;
  return *this;
}

template <class T>
T& generic_vec3<T>::x() {
  return (*this)[0];
}

template <class T>
T const& generic_vec3<T>::x() const {
  return (*this)[0];
}

template <class T>
T& generic_vec3<T>::y() {
  return (*this)[1];
}

template <class T>
T const& generic_vec3<T>::y() const {
  return (*this)[1];
}

template <class T>
T& generic_vec3<T>::z() {
  return (*this)[2];
}

template <class T>
T const& generic_vec3<T>::z() const {
  return (*this)[2];
}

template <class T>
generic_vec3<T> generic_vec3<T>::cross(generic_vec3<T> const& other) const {
  return generic_vec3<T>(                 //
      y() * other.z() - other.y() * z(),  //
      z() * other.x() - other.z() * x(),  //
      x() * other.y() - other.x() * y()   //
  );                                      //
}

}  // namespace math

}  // namespace orbitals
