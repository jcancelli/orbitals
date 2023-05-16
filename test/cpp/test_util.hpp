#pragma once

#include <complex>
#include <type_traits>

#include "doctest.h"
#include "math/matrix.hpp"
#include "math/quaternion.hpp"
#include "math/vector.hpp"

using orbitals::math::mat;
using orbitals::math::quat;
using orbitals::math::vec;

template <std::size_t vecSize, class T>
inline void CHECK_VEC_EQUALS(vec<vecSize, T> const& v1, vec<vecSize, T> const& v2,
                             float epsilon = .00001) {
  INFO("Comparing ", v1, " == ", v2);
  for (int i = 0; i < vecSize; i++) {
    INFO("i: ", i);
    CHECK(v1[i] == doctest::Approx(v2[i]).epsilon(epsilon));
  }
}

template <class T>
inline void CHECK_QUAT_EQUALS(quat<T> const& q1, quat<T> const& q2, float epsilon = .00001) {
  INFO("Comparing ", q1, " == ", q2);
  CHECK(q1.x == doctest::Approx(q2.x).epsilon(epsilon));
  CHECK(q1.y == doctest::Approx(q2.y).epsilon(epsilon));
  CHECK(q1.z == doctest::Approx(q2.z).epsilon(epsilon));
  CHECK(q1.w == doctest::Approx(q2.w).epsilon(epsilon));
}

template <std::size_t tRows, std::size_t tCols, class T>
inline void CHECK_MAT_EQUALS(mat<tRows, tCols, T> const& m1, mat<tRows, tCols, T> const& m2,
                             float epsilon = .00001) {
  INFO("Comparing ", m1, " == ", m2);
  for (int row = 0; row < tRows; row++) {
    for (int col = 0; col < tCols; col++) {
      INFO("row: ", row, ", col: ", col);
      CHECK(m1(col, row) == doctest::Approx(m2(col, row)).epsilon(epsilon));
    }
  }
}

template <class T>
inline void CHECK_COMPLEX_EQUALS(std::complex<T> const& a, std::complex<T> const& b,
                                 float epsilon = .00001) {
  INFO("Comparing ", a, " == ", b);
  CHECK(a.real() == doctest::Approx(b.real()).epsilon(epsilon));
  CHECK(a.imag() == doctest::Approx(b.imag()).epsilon(epsilon));
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
inline void CHECK_SIGN_EQUALS(T a, T b) {
  INFO("Checking sign of ", a, " == ", b);
  bool result = std::signbit(a) == std::signbit(b) || (a == T(0) && b == T(0));
  CHECK(result);
}

template <class T, class = std::enable_if_t<std::is_arithmetic_v<T>>>
inline void CHECK_COMPLEX_SIGN_EQUALS(std::complex<T> const& a, std::complex<T> const& b) {
  INFO("Checking sign of ", a, " == ", b);
  CHECK_SIGN_EQUALS(a.real(), b.real());
  CHECK_SIGN_EQUALS(a.imag(), b.imag());
}