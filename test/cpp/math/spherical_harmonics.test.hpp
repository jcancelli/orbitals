#pragma once

#include <complex>
#include <string>

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/spherical_harmonics.hpp"
#include "math/trigonometry.hpp"

using namespace orbitals::math;
using namespace std::string_literals;
using std::complex;

// source: https://en.wikipedia.org/wiki/Table_of_spherical_harmonics
TEST_CASE("Testing spherical harmonics") {
  SphericalHarmonics Y;

  const complex<double> i(0, 1);

  for (int degTheta = 0; degTheta < 180; degTheta += 44) {
    const double theta = radians(degTheta);
    Y.setTheta(theta);
    SUBCASE(("theta: "s + std::to_string(degrees(theta)) + "°").c_str()) {
      for (int degPhi = 0; degPhi <= 360; degPhi += 45) {
        const double phi = radians(degPhi);
        Y.setPhi(phi);
        SUBCASE(("phi: "s + std::to_string(degrees(phi)) + "°").c_str()) {
          SUBCASE("l (degree): 0") {
            Y.setDegree(0);

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<double> expected = 0.5 * sqrt(1 / M_PI);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 1") {
            Y.setDegree(1);

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<double> expected =
                  0.5 * sqrt(3 / (2 * M_PI)) * exp(-i * phi) * sin(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<double> expected = 0.5 * sqrt(3 / M_PI) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<double> expected =
                  -0.5 * sqrt(3 / (2 * M_PI)) * exp(i * phi) * sin(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 2") {
            Y.setDegree(2);

            SUBCASE("m (order): -2") {
              Y.setOrder(-2);
              const complex<double> expected =
                  0.25 * sqrt(15 / (2 * M_PI)) * exp(-i * 2. * phi) * pow(sin(theta), 2);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<double> expected =
                  0.5f * sqrt(15 / (2 * M_PI)) * exp(-i * phi) * sin(theta) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<double> expected =
                  0.25f * sqrt(5 / M_PI) * (3 * pow(cos(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<double> expected =
                  -0.5 * sqrt(15 / (2 * M_PI)) * exp(i * phi) * sin(theta) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 2") {
              Y.setOrder(2);
              const complex<double> expected =
                  0.25 * sqrt(15 / (2 * M_PI)) * exp(i * 2. * phi) * pow(sin(theta), 2);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 3") {
            Y.setDegree(3);

            SUBCASE("m (order): -3") {
              Y.setOrder(-3);
              const complex<double> expected =
                  0.125 * sqrt(35 / M_PI) * exp(-i * 3. * phi) * pow(sin(theta), 3);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -2") {
              Y.setOrder(-2);
              const complex<double> expected = 0.25 * sqrt(105 / (2 * M_PI)) * exp(-i * 2. * phi) *
                                               pow(sin(theta), 2) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<double> expected = 0.125 * sqrt(21 / M_PI) * exp(-i * phi) *
                                               sin(theta) * (5 * pow(cos(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<double> expected =
                  0.25 * sqrt(7 / M_PI) * ((5 * pow(cos(theta), 3)) - (3 * cos(theta)));
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<double> expected = -0.125 * sqrt(21 / M_PI) * exp(i * phi) *
                                               sin(theta) * (5 * pow(cos(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 2") {
              Y.setOrder(2);
              const complex<double> expected = 0.25 * sqrt(105 / (2 * M_PI)) * exp(i * 2. * phi) *
                                               pow(sin(theta), 2) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 3") {
              Y.setOrder(3);
              const complex<double> expected =
                  -0.125 * sqrt(35 / M_PI) * exp(i * 3. * phi) * pow(sin(theta), 3);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }
          }

          SUBCASE("l (degree): 4") {
            Y.setDegree(4);

            SUBCASE("m (order): -4") {
              Y.setOrder(-4);
              const complex<double> expected =
                  (3. / 16.) * sqrt(35 / (2 * M_PI)) * exp(-i * 4. * phi) * pow(sin(theta), 4);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -3") {
              Y.setOrder(-3);
              const complex<double> expected = (3. / 8.) * sqrt(35 / M_PI) * exp(-i * 3. * phi) *
                                               pow(sin(theta), 3) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -2") {
              Y.setOrder(-2);
              const complex<double> expected = (3. / 8.) * sqrt(5 / (2 * M_PI)) *
                                               exp(-i * 2. * phi) * pow(sin(theta), 2) *
                                               (7 * pow(cos(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): -1") {
              Y.setOrder(-1);
              const complex<double> expected = (3. / 8.) * sqrt(5 / M_PI) * exp(-i * phi) *
                                               sin(theta) *
                                               ((7 * pow(cos(theta), 3)) - (3 * cos(theta)));
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 0") {
              Y.setOrder(0);
              const complex<double> expected =
                  (3. / 16.) * sqrt(1 / M_PI) *
                  ((35 * pow(cos(theta), 4)) - (30 * pow(cos(theta), 2)) + 3);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 1") {
              Y.setOrder(1);
              const complex<double> expected = (-3. / 8.) * sqrt(5 / M_PI) * exp(i * phi) *
                                               sin(theta) *
                                               ((7 * pow(cos(theta), 3)) - (3 * cos(theta)));
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 2") {
              Y.setOrder(2);
              const complex<double> expected = (3. / 8.) * sqrt(5 / (2 * M_PI)) *
                                               exp(i * 2. * phi) * pow(sin(theta), 2) *
                                               (7 * pow(cos(theta), 2) - 1);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 3") {
              Y.setOrder(3);
              const complex<double> expected = (-3. / 8.) * sqrt(35 / M_PI) * exp(i * 3. * phi) *
                                               pow(sin(theta), 3) * cos(theta);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }

            SUBCASE("m (order): 4") {
              Y.setOrder(4);
              const complex<double> expected =
                  (3. / 16.) * sqrt(35 / (2 * M_PI)) * exp(i * 4. * phi) * pow(sin(theta), 4);
              CHECK_COMPLEX_EQUALS(Y(), expected);
              CHECK_COMPLEX_SIGN_EQUALS(Y(), expected);
            }
          }
        }
      }
    }
  }
}