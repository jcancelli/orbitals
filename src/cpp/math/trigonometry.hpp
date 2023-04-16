#pragma once

#include <type_traits>

#include "vector.hpp"

namespace orbitals {

namespace math {

template <typename T>
inline T radians(T deg) {
  static_assert(std::is_arithmetic<T>::value, "Invalid parameter type");
  return deg * static_cast<T>(0.01745329251994329576923690768489);
}

template <typename T>
inline T degrees(T rad) {
  static_assert(std::is_arithmetic<T>::value, "Invalid parameter type");
  return rad * static_cast<T>(57.295779513082320876798154814105);
}

}  // namespace math

}  // namespace orbitals