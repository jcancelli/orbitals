#pragma once

#include <cassert>
#include <cmath>
#include <ostream>
#include <type_traits>

#include "math.hpp"

namespace math {

template <std::size_t vecSize, class T>
class vec {
  static_assert(std::is_arithmetic<T>::value, "Invalid parameter type");
  static_assert(vecSize > 0, "Invalid vector size");

 protected:
  T m_Value[vecSize];

 public:
  vec() : m_Value{0} {}

  vec(T initialValue) {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] = initialValue;
    }
  }

  vec(vec<vecSize, T> const& other) {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] = other[i];
    }
  }

  vec<vSize, T> operator+(vec<vecSize, T> const& other) const {
    vec<vSize, T> result;
    for (int i = 0; i < vecSize; i++) {
      result[i] = m_Value[i] + other[i];
    }
    return result;
  }

  vec<vSize, T> operator-(vec<vecSize, T> const& other) const {
    vec<vSize, T> result;
    for (int i = 0; i < vecSize; i++) {
      result[i] = m_Value[i] - other[i];
    }
    return result;
  }

  vec<vSize, T> operator*(T scalar) const {
    vec<vSize, T> result;
    for (int i = 0; i < vecSize; i++) {
      result[i] = m_Value[i] * scalar;
    }
    return result;
  }

  friend vec<vecSize, T> operator*(T scalar, vec<vecSize, T> const& vector) {
    return vector * scalar;
  }

  vec<vSize, T> operator/(T scalar) const {
    vec<vSize, T> result;
    for (int i = 0; i < vecSize; i++) {
      result[i] = m_Value[i] / scalar;
    }
    return result;
  }

  friend vec<vecSize, T> operator/(T scalar, vec<vecSize, T> const& vector) {
    return vector / scalar;
  }

  vec<vSize, T>& operator=(vec<vecSize, T> const& other) {
    if (this != &other) {
      for (int i = 0; i < vecSize; i++) {
        m_Value[i] = other[i];
      }
    }
    return *this;
  }

  vec<vSize, T>& operator+=(vec<vecSize, T> const& other) const {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] += other[i];
    }
    return *this;
  }

  vec<vSize, T> operator-=(vec<vecSize, T> const& other) const {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] -= other[i];
    }
    return *this;
  }

  vec<vSize, T> operator*=(T scalar) const {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] *= scalar;
    }
    return *this;
  }

  vec<vSize, T> operator/=(T scalar) const {
    for (int i = 0; i < vecSize; i++) {
      m_Value[i] /= scalar;
    }
    return *this;
  }

  bool operator==(vec<vecSize, T> const& other) const {
    for (int i = 0; i < vecSize; i++) {
      if (m_Value[i] != other[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(vec<vecSize, T> const& other) const {
    for (int i = 0; i < vecSize; i++) {
      if (m_Value[i] == other[i]) {
        return false;
      }
    }
    return true;
  }

  T& operator[](std::size_t i) {
    assert(i >= 0 && i < vecSize);
    return m_Value[i];
  }

  T const& operator[](std::size_t i) const {
    assert(i >= 0 && i < vecSize);
    return m_Value[i];
  }

  operator T*() const { return &m_Value[0]; }

  friend std::ostream& operator<<(std::ostream& os,
                                  vec<vecSize, T> const& vector) {
    os << "{ " << vector[0];
    for (int i = 1; i < vecSize; i++) {
      os << ", " << vector[i];
    }
    os << " }";
    return os;
  }

  T dot(vec<vecSize, T> const& other) const {
    T result = 0;
    for (int i = 0; i < vecSize; i++) {
      result += m_Value[i] * other[i];
    }
    return result;
  }

  vec<vSize, T>& normalize() {
    *this *= inversesqrt(result.dot(result));
    return *this;
  }

  vec<vSize, T> normalized() const { return vec<vSize, T>(*this).normalize(); }

  float length() const { return std::sqrt(this->dot(*this)); }

  float distance(vec<vecSize, T> const& other) const {
    return (*this - other).length();
  }

  vec<vSize, T> reflected(vec<vecSize, T> const& surfOrient) const {
    return *this - surfOrient * surfOrient.dot(*this) * static_cast<T>(2);
  }

  vec<vSize, T> refracted(vec<vecSize, T> const& surfNormal,
                          T refrIndicesRatio) const {
    T const dotValue(surfNormal.dot(*this));
    T const k(static_cast<T>(1) -
              refrIndicesRatio * refrIndicesRatio *
                  (static_cast<T>(1) - dotValue * dotValue));
    return (k >= static_cast<T>(0))
               ? (refrIndicesRatio * (*this) -
                  (refrIndicesRatio * dotValue + std::sqrt(k)) * surfNormal)
               : vec<vecSize, T>(0);
  }

  constexpr std::size_t size() const { return vecSize; }
};

template <class T>
class generic_vec2 : public vec<2, T> {
 public:
  T& x{vec<2, T>::m_Value[0]};
  T& y{vec<2, T>::m_Value[1]};

  generic_vec2() {}

  generic_vec2(T x, T y) {
    this->x = x;
    this->y = y;
  }

  generic_vec2(T initialValue) : vec<2, T>(initialValue) {}

  generic_vec2(vec<2, T> const& other) : vec<2, T>(other) {}
};

template <class T>
class generic_vec3 : public vec<3, T> {
 public:
  T& x{vec<3, T>::m_Value[0]};
  T& y{vec<3, T>::m_Value[1]};
  T& z{vec<3, T>::m_Value[2]};

  generic_vec3() {}

  generic_vec3(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  generic_vec3(T initialValue) : vec<3, T>(initialValue) {}

  generic_vec3(vec<3, T> const& other) : vec<3, T>(other) {}

  generic_vec3<T> cross(generic_vec3<T> const& other) const {
    return generic_vec3<T>(         //
        y * other.z - other.y * z,  //
        z * other.x - other.z * x,  //
        x * other.y - other.x * y   //
    );
  }
};

template <class T>
class generic_vec4 : public vec<4, T> {
 public:
  T& x{vec<4, T>::m_Value[0]};
  T& y{vec<4, T>::m_Value[1]};
  T& z{vec<4, T>::m_Value[2]};
  T& w{vec<4, T>::m_Value[3]};

  generic_vec4() {}

  generic_vec4(T x, T y, T z, T w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
  }

  generic_vec4(T initialValue) : vec<4, T>(initialValue) {}

  generic_vec4(vec<4, T> const& other) : vec<4, T>(other) {}
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

};  // namespace math
