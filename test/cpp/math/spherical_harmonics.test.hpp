#pragma once

#include <complex>
#include <string>

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/spherical_harmonics.hpp"

using namespace orbitals::math;
using namespace std::string_literals;
using std::complex;

// source: https://en.wikipedia.org/wiki/Table_of_spherical_harmonics
TEST_CASE("Testing spherical harmonics") {
  SphericalHarmonics Y;

  const complex<float> i(0, 1);

  // l: degree
  // m: order

  for (float theta = 0; theta <= M_PI + .00001f; theta += radians(45)) {
    Y.setTheta(theta);
    SUBCASE(("theta: "s + std::to_string(degrees(theta)) + "°").c_str()) {
      for (float phi = 0; phi <= M_PI * 2 + .00001f; phi += radians(45)) {
        Y.setPhi(phi);
        SUBCASE(("phi: "s + std::to_string(degrees(phi)) + "°").c_str()) {
          SUBCASE("l (degree): 0") {
            Y.setDegree(0);

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<float> expected = 0.5f * sqrtf(1 / M_PI);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 1") {
            Y.setDegree(1);

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<float> expected =
                  0.5f * sqrtf(3 / (2 * M_PI)) * exp(-i * phi) * sinf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<float> expected = 0.5f * sqrtf(3 / M_PI) * cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<float> expected =
                  -0.5f * sqrtf(3 / (2 * M_PI)) * exp(i * phi) * sinf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 2") {
            Y.setDegree(2);

            SUBCASE("m (order): -2") {
              Y.setOrder(-2);
              const complex<float> expected =
                  0.25f * sqrtf(15 / (2 * M_PI)) * exp(-i * 2.f * phi) * powf(sinf(theta), 2);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<float> expected =
                  0.5f * sqrtf(15 / (2 * M_PI)) * exp(-i * phi) * sinf(theta) * cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<float> expected =
                  0.25f * sqrtf(5 / M_PI) * (3 * powf(cosf(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<float> expected =
                  -0.5f * sqrtf(15 / (2 * M_PI)) * exp(i * phi) * sinf(theta) * cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 2") {
              Y.setOrder(2);
              const complex<float> expected =
                  0.25f * sqrtf(15 / (2 * M_PI)) * exp(i * 2.f * phi) * powf(sinf(theta), 2);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 3") {
            Y.setDegree(3);

            SUBCASE("m (order): -3") {
              Y.setOrder(-3);
              const complex<float> expected =
                  0.125f * sqrtf(35 / M_PI) * exp(-i * 3.f * phi) * powf(sinf(theta), 3);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -2") {
              Y.setOrder(-2);
              const complex<float> expected = 0.25f * sqrtf(105 / (2 * M_PI)) *
                                              exp(-i * 2.f * phi) * powf(sinf(theta), 2) *
                                              cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<float> expected = 0.125f * sqrtf(21 / M_PI) * exp(-i * phi) *
                                              sinf(theta) * (5 * powf(cosf(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<float> expected =
                  0.25f * sqrtf(7 / M_PI) * ((5 * powf(cosf(theta), 3)) - (3 * cosf(theta)));
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<float> expected = -0.125f * sqrtf(21 / M_PI) * exp(i * phi) *
                                              sinf(theta) * (5 * powf(cosf(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 2") {
              Y.setOrder(2);
              const complex<float> expected = 0.25f * sqrtf(105 / (2 * M_PI)) * exp(i * 2.f * phi) *
                                              powf(sinf(theta), 2) * cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 3") {
              Y.setOrder(3);
              const complex<float> expected =
                  -0.125f * sqrtf(35 / M_PI) * exp(i * 3.f * phi) * powf(sinf(theta), 3);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 4") {
            Y.setDegree(4);

            SUBCASE("m (order): -4") {
              Y.setOrder(-4);
              const complex<float> expected = (3.f / 16.f) * sqrtf(35 / (2 * M_PI)) *
                                              exp(-i * 4.f * phi) * powf(sinf(theta), 4);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -3") {
              Y.setOrder(-3);
              const complex<float> expected = (3.f / 8.f) * sqrtf(35 / M_PI) * exp(-i * 3.f * phi) *
                                              powf(sinf(theta), 3) * cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -2") {
              Y.setOrder(-2);
              const complex<float> expected = (3.f / 8.f) * sqrtf(5 / (2 * M_PI)) *
                                              exp(-i * 2.f * phi) * powf(sinf(theta), 2) *
                                              (7 * powf(cosf(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<float> expected = (3.f / 8.f) * sqrtf(5 / M_PI) * exp(-i * phi) *
                                              sinf(theta) *
                                              ((7 * powf(cosf(theta), 3)) - (3 * cosf(theta)));
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<float> expected =
                  (3.f / 16.f) * sqrtf(1 / M_PI) *
                  ((35 * powf(cosf(theta), 4)) - (30 * powf(cosf(theta), 2)) + 3);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<float> expected = (-3.f / 8.f) * sqrtf(5 / M_PI) * exp(i * phi) *
                                              sinf(theta) *
                                              ((7 * powf(cosf(theta), 3)) - (3 * cosf(theta)));
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 2") {
              Y.setOrder(2);
              const complex<float> expected = (3.f / 8.f) * sqrtf(5 / (2 * M_PI)) *
                                              exp(i * 2.f * phi) * powf(sinf(theta), 2) *
                                              (7 * powf(cosf(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 3") {
              Y.setOrder(3);
              const complex<float> expected = (-3.f / 8.f) * sqrtf(35 / M_PI) * exp(i * 3.f * phi) *
                                              powf(sinf(theta), 3) * cosf(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 4") {
              Y.setOrder(4);
              const complex<float> expected =
                  (3.f / 16.f) * sqrtf(35 / (2 * M_PI)) * exp(i * 4.f * phi) * powf(sinf(theta), 4);
              CHECK_COMPLEX_EQUALS(Y(), expected);
            }
          }
        }
      }
    }
  }
}