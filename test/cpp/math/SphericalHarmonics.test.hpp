#pragma once

#include <complex>

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/SphericalHarmonics.hpp"

using namespace orbitals::math;

TEST_CASE("Testing spherical harmonics") {
  SphericalHarmonics Y;
  const float theta = 0;
  const float phi = 0;

  SUBCASE("degree: 0") {
    Y.setDegree(0);
    SUBCASE("order: 0") {
      Y.setOrder(0);
      std::complex<float> expected(0.5f * sqrtf(1 / M_PI), 0);
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }
  }

  SUBCASE("degree: 1") {
    Y.setDegree(1);

    SUBCASE("order: -1") {
      Y.setOrder(-1);
      std::complex<float> expected =
          0.5f * sqrtf(3 / (2 * M_PI)) * sinf(theta) * exp(phi * (-std::complex<float>(0, 1)));
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }

    SUBCASE("order: 0") {
      Y.setOrder(0);
      std::complex<float> expected = 0.5f * sqrtf(3 / (M_PI)) * cosf(theta);
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }

    SUBCASE("order: 1") {
      Y.setOrder(1);
      std::complex<float> expected =
          -0.5f * sqrtf(3 / (2 * M_PI)) * sinf(theta) * exp(phi * std::complex<float>(0, 1));
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }
  }

  SUBCASE("degree: 2") {
    Y.setDegree(2);

    SUBCASE("order: -2") {
      Y.setOrder(-2);
      std::complex<float> expected = 0.25f * sqrtf(15 / (2 * M_PI)) * sinf(theta) * sinf(theta) *
                                     exp(2 * phi * (-std::complex<float>(0, 1)));
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }

    SUBCASE("order: -1") {
      Y.setOrder(-1);
      std::complex<float> expected = 0.5f * sqrtf(15 / M_PI) * sinf(theta) * cosf(theta) *
                                     exp(phi * (-std::complex<float>(0, 1)));
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }

    SUBCASE("order: 0") {
      Y.setOrder(0);
      std::complex<float> expected = 0.25f * sqrtf(5 / M_PI) * (3 * cosf(theta) * cosf(theta) - 1);
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }

    SUBCASE("order: 1") {
      Y.setOrder(1);
      std::complex<float> expected = -0.5f * sqrtf(15 / (2 * M_PI)) * sinf(theta) * cosf(theta) *
                                     exp(phi * std::complex<float>(0, 1));
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }

    SUBCASE("order: 2") {
      Y.setOrder(2);
      std::complex<float> expected = 0.25f * sqrtf(15 / (2 * M_PI)) * sinf(theta) * sinf(theta) *
                                     exp(2 * phi * std::complex<float>(0, 1));
      CHECK_COMPLEX_EQUALS(Y(theta, phi), expected);
    }
  }
}