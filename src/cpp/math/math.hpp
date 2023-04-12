#pragma once

#include <cmath>
#include <type_traits>

namespace math {

template <typename T>
inline T inversesqrt(T value) {
  static_assert(std::is_arithmetic<T>::value, "Invalid parameter type");
  return static_cast<T>(1) / std::sqrt(value);
}

};  // namespace math