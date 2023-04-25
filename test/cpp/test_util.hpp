#pragma once

#include <type_traits>

#include "doctest.h"
#include "math/matrix.hpp"
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

template <std::size_t tRows, std::size_t tCols, class T>
inline void CHECK_MAT_EQUALS(mat<tRows, tCols, T> const& m1, mat<tRows, tCols, T> const& m2) {
  INFO("Comparing ", m1, " == ", m2);
  for (int row = 0; row < tRows; row++) {
    for (int col = 0; col < tCols; col++) {
      INFO("row: ", row, ", col: ", col);
      CHECK(m1(col, row) == doctest::Approx(m2(col, row)));
    }
  }
}
