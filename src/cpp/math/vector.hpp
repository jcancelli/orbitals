#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <ostream>
#include <type_traits>

#include "math.hpp"

namespace orbitals {

namespace math {

template <std::size_t vecSize, class T>
class vec {
  static_assert(vecSize > 0);
  static_assert(std::is_arithmetic<T>::value);

 private:
  std::array<T, vecSize> m_Value;

 public:
  vec();
  explicit vec(T initialValue);
  vec(vec<vecSize, T> const& other);

  vec<vecSize, T> operator+(vec<vecSize, T> const& other) const;
  vec<vecSize, T> operator-(vec<vecSize, T> const& other) const;

  vec<vecSize, T>& operator=(vec<vecSize, T> const& other);

  vec<vecSize, T>& operator+=(vec<vecSize, T> const& other);
  vec<vecSize, T>& operator-=(vec<vecSize, T> const& other);
  vec<vecSize, T>& operator*=(T scalar);
  vec<vecSize, T>& operator/=(T scalar);

  bool operator==(vec<vecSize, T> const& other) const;
  bool operator!=(vec<vecSize, T> const& other) const;

  T& operator[](std::size_t i);
  T const& operator[](std::size_t i) const;

  T const* data() const;
  T* data();

  T dot(vec<vecSize, T> const& other) const;

  vec<vecSize, T>& normalize();
  vec<vecSize, T> normalized() const;

  vec<vecSize, T> reflected(vec<vecSize, T> const& surfOrient) const;
  vec<vecSize, T> refracted(vec<vecSize, T> const& surfNormal, T refrIndicesRatio) const;

  float length() const;
  float distance(vec<vecSize, T> const& other) const;

  constexpr std::size_t size() const;
};

template <std::size_t vecSize, class T, class Scalar, class>
inline vec<vecSize, T> operator*(vec<vecSize, T> const& vector, Scalar scalar);
template <std::size_t vecSize, class T, class Scalar, class>
inline vec<vecSize, T> operator*(Scalar scalar, vec<vecSize, T> const& vector);
template <std::size_t vecSize, class T, class Scalar, class>
inline vec<vecSize, T> operator/(vec<vecSize, T> const& vector, Scalar scalar);
template <std::size_t vecSize, class T>
inline std::ostream& operator<<(std::ostream& os, vec<vecSize, T> const& vector);

template <class T>
class generic_vec2 : public vec<2, T> {
 public:
  generic_vec2();
  generic_vec2(T x, T y);
  generic_vec2(T initialValue);
  generic_vec2(vec<2, T> const& other);

  generic_vec2<T>& operator=(vec<2, T> const& other);
  generic_vec2<T>& operator()(T x, T y);

  T& x();
  T const& x() const;
  T& y();
  T const& y() const;
};

template <class T>
class generic_vec3 : public vec<3, T> {
 public:
  generic_vec3();
  generic_vec3(T x, T y, T z);
  generic_vec3(T initialValue);
  generic_vec3(vec<3, T> const& other);

  generic_vec3<T> cross(generic_vec3<T> const& other) const;
  generic_vec3<T>& operator=(vec<3, T> const& other);
  generic_vec3<T>& operator()(T x, T y, T z);

  T& x();
  T const& x() const;
  T& y();
  T const& y() const;
  T& z();
  T const& z() const;
};

template <class T>
class generic_vec4 : public vec<4, T> {
 public:
  generic_vec4();
  generic_vec4(T x, T y, T z, T w);
  generic_vec4(T initialValue);
  generic_vec4(vec<4, T> const& other);

  generic_vec4<T>& operator=(vec<4, T> const& other);
  generic_vec4<T>& operator()(T x, T y, T z, T w);

  T& x();
  T const& x() const;
  T& y();
  T const& y() const;
  T& z();
  T const& z() const;
  T& w();
  T const& w() const;
};

using vec2 = generic_vec2<float>;
using vec3 = generic_vec3<float>;
using vec4 = generic_vec4<float>;
using ivec2 = generic_vec2<int>;
using ivec3 = generic_vec3<int>;
using ivec4 = generic_vec4<int>;
using uivec2 = generic_vec2<unsigned int>;
using uivec3 = generic_vec3<unsigned int>;
using uivec4 = generic_vec4<unsigned int>;

}  // namespace math

}  // namespace orbitals

#include "vector_generic_vec2.inl"
#include "vector_generic_vec3.inl"
#include "vector_generic_vec4.inl"
#include "vector_vec.inl"