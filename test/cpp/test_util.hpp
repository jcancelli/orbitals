#pragma once

#include <type_traits>

#include "doctest.h"
#include "math/vector.hpp"

using orbitals::math::vec;

template <std::size_t vecSize, class T>
inline void CHECK_VEC_EQUALS(vec<vecSize, T> const& v1, vec<vecSize, T> const& v2) {
  INFO("Comparing ", v1, " == ", v2);
  for (int i = 0; i < vecSize; i++) {
    INFO("i: ", i);
    CHECK(v1[i] == doctest::Approx(v2[i]));
  }
}
