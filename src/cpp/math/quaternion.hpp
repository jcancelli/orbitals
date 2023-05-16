#pragma once

#include <ostream>
#include <type_traits>

#include "vector.hpp"

namespace orbitals {

namespace math {

template <class T>
class quat {
  static_assert(std::is_arithmetic_v<T>);

 public:
  T x, y, z, w;

 public:
  quat();
  explicit quat(quat<T> const& other);
  explicit quat(generic_vec3<T> const& eulerAngle);
  explicit quat(T angle, generic_vec3<T> const& axis);
  explicit quat(T x, T y, T z, T w);

  quat<T> conjugate() const;
  quat<T> inverse() const;
  quat<T> normalized() const;
  T dot(quat<T> const& other) const;
  double length() const;

  quat<T> operator+(quat<T> const& other) const;
  quat<T> operator-(quat<T> const& other) const;

  quat<T> operator*(quat<T> const& other) const;

  generic_vec3<T> operator*(generic_vec3<T> const& v) const;

  quat<T> operator*(T scalar) const;
  quat<T> operator/(T scalar) const;

  quat<T>& operator=(quat<T> const& other);
  quat<T>& operator+=(quat<T> const& other);
  quat<T>& operator-=(quat<T> const& other);
  quat<T>& operator*=(quat<T> const& other);

  bool operator==(quat<T> const& other) const;
  bool operator!=(quat<T> const& other) const;

  T& operator[](std::size_t i);
  T const& operator[](std::size_t i) const;
};

template <class T>
generic_vec3<T> operator*(generic_vec3<T> const& v, quat<T> const& q);
template <class T>
quat<T> operator*(T scalar, quat<T> const& q);
template <class T>
std::ostream& operator<<(std::ostream& os, quat<T> const& q);

using quatf = quat<float>;
using quati = quat<int>;
using quatui = quat<unsigned int>;

}  // namespace math

}  // namespace orbitals

#include "quaternion.inl"