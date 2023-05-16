#pragma once

#include <cassert>
#include <iostream>

#include "quaternion.hpp"

namespace orbitals {

namespace math {

template <class T>
quat<T>::quat() : x{0}, y{0}, z{0}, w{0} {
}

template <class T>
quat<T>::quat(quat<T> const& other) : x{other.x}, y{other.y}, z{other.z}, w{other.w} {
}

template <class T>
quat<T>::quat(generic_vec3<T> const& eulerAngle) {
  generic_vec3<T> half = eulerAngle * 0.5;
  generic_vec3<T> c(std::cos(half[0]), std::cos(half[1]), std::cos(half[2]));
  generic_vec3<T> s(std::sin(half[0]), std::sin(half[1]), std::sin(half[2]));

  w = c.x() * c.y() * c.z() + s.x() * s.y() * s.z();
  x = s.x() * c.y() * c.z() - c.x() * s.y() * s.z();
  y = c.x() * s.y() * c.z() + s.x() * c.y() * s.z();
  z = c.x() * c.y() * s.z() - s.x() * s.y() * c.z();
}

template <class T>
quat<T>::quat(T angle, generic_vec3<T> const& axis)
    : x{axis.x()}, y{axis.y()}, z{axis.z()}, w{angle} {
}

template <class T>
quat<T>::quat(T x, T y, T z, T w) : x{x}, y{y}, z{z}, w{w} {
}

template <class T>
quat<T> quat<T>::conjugate() const {
  return quat<T>(-x, -y, -z, w);
}

template <class T>
quat<T> quat<T>::inverse() const {
  assert(*this != quat<T>(0));
  return conjugate() / dot(*this);
}

template <class T>
quat<T> quat<T>::normalized() const {
  return *this * (1 / length());
}

template <class T>
T quat<T>::dot(quat<T> const& other) const {
  return w * other.w + x * other.x + y * other.y + z * other.z;
}

template <class T>
double quat<T>::length() const {
  return std::sqrt(x * x + y * y + z * z + w * w);
}

template <class T>
quat<T> quat<T>::operator+(quat<T> const& other) const {
  return quat<T>(x + other.x, y + other.y, z + other.z, w + other.w);
}

template <class T>
quat<T> quat<T>::operator-(quat<T> const& other) const {
  return quat<T>(x - other.x, y - other.y, z - other.z, w - other.w);
}

template <class T>
quat<T> quat<T>::operator*(quat<T> const& other) const {
  return quat<T>(                                             //
      w * other.x + x * other.w + y * other.z - z * other.y,  //
      w * other.y + y * other.w + z * other.x - x * other.z,  //
      w * other.z + z * other.w + x * other.y - y * other.x,  //
      w * other.w - x * other.x - y * other.y - z * other.z   //
  );                                                          //
}

template <class T>
quat<T> quat<T>::operator*(T scalar) const {
  return quat<T>(x * scalar, y * scalar, z * scalar, w * scalar);
}

template <class T>
quat<T> quat<T>::operator/(T scalar) const {
  return quat<T>(x / scalar, y / scalar, z / scalar, w / scalar);
}

template <class T>
quat<T> operator*(T scalar, quat<T> const& q) {
  return q * scalar;
}

template <class T>
generic_vec3<T> quat<T>::operator*(generic_vec3<T> const& v) const {
  generic_vec3<T> quatVec(x, y, z);
  generic_vec3<T> uv(quatVec.cross(v));
  generic_vec3<T> uuv(quatVec.cross(uv));

  return v + ((uv * w) + uuv) * static_cast<T>(2);
}

template <class T>
generic_vec3<T> operator*(generic_vec3<T> const& v, quat<T> const& q) {
  return q.inverse() * v;
}

template <class T>
quat<T>& quat<T>::operator=(quat<T> const& other) {
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;
  return *this;
}

template <class T>
quat<T>& quat<T>::operator+=(quat<T> const& other) {
  *this = *this + other;
  return *this;
}

template <class T>
quat<T>& quat<T>::operator-=(quat<T> const& other) {
  *this = *this - other;
  return *this;
}

template <class T>
quat<T>& quat<T>::operator*=(quat<T> const& other) {
  *this = *this * other;
  return *this;
}

template <class T>
bool quat<T>::operator==(quat<T> const& other) const {
  return (             //
      x == other.x &&  //
      y == other.y &&  //
      z == other.z &&  //
      w == other.w     //
  );                   //
}

template <class T>
bool quat<T>::operator!=(quat<T> const& other) const {
  return !(*this == other);
}

template <class T>
T& quat<T>::operator[](std::size_t i) {
  switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      assert(false);
  }
}

template <class T>
T const& quat<T>::operator[](std::size_t i) const {
  switch (i) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      assert(false);
  }
}

template <class T>
std::ostream& operator<<(std::ostream& os, quat<T> const& q) {
  return os << "{" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << "}";
}

}  // namespace math

}  // namespace orbitals
