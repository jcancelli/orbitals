#pragma once

#include <string>

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/bohr.hpp"
#include "math/trigonometry.hpp"
#include "math/wave_function.hpp"

using namespace orbitals::math;
using namespace std::string_literals;

// source: https://employees.csbsju.edu/hjakubowski/classes/ch123/Quantum/EquationsOribtalsH.htm
TEST_CASE("Testing wave function") {
  WaveFunction psi;

  const std::complex<double> i(0, 1);

  for (double r = 0; r < 2; r++) {
    psi.setR(BOHR_TO_PM(r));

    SUBCASE(("r: "s + std::to_string(int(r)) + " bohrs").c_str()) {
      for (int degTheta = 0; degTheta < 180; degTheta += 44) {
        const double theta = radians(degTheta);
        psi.setTheta(theta);

        SUBCASE(("theta: "s + std::to_string(degTheta) + "°").c_str()) {
          for (int degPhi = 0; degPhi < 360; degPhi += 44) {
            const double phi = radians(degPhi);
            psi.setPhi(phi);

            SUBCASE(("phi: "s + std::to_string(degPhi) + "°").c_str()) {
              SUBCASE("n: 1") {
                psi.setN(1);

                SUBCASE("l: 0") {
                  psi.setL(0);

                  SUBCASE("m: 0") {
                    psi.setM(0);

                    const std::complex<double> expected((1 / sqrt(M_PI)) * exp(-r), 0);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }
                }
              }

              SUBCASE("n: 2") {
                psi.setN(2);

                SUBCASE("l: 0") {
                  psi.setL(0);

                  SUBCASE("m: 0") {
                    psi.setM(0);

                    const std::complex<double> expected =
                        (1 / (4 * sqrt(2 * M_PI))) * (2 - r) * exp(-r / 2);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }
                }

                SUBCASE("l: 1") {
                  psi.setL(1);

                  SUBCASE("m: -1") {
                    psi.setM(-1);
                    const std::complex<double> expected =
                        0.125 * (1 / sqrt(M_PI)) * r * exp(-r / 2) * sin(theta) * exp(-i * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 0") {
                    psi.setM(0);
                    const std::complex<double> expected =
                        (1 / sqrt(32 * M_PI)) * r * exp(-r / 2) * cos(theta);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 1") {
                    psi.setM(1);
                    const std::complex<double> expected =
                        0.125 * (1 / sqrt(M_PI)) * r * exp(-r / 2) * sin(theta) * exp(i * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }
                }
              }

              SUBCASE("n: 3") {
                psi.setN(3);

                SUBCASE("l: 0") {
                  psi.setL(0);

                  SUBCASE("m: 0") {
                    psi.setM(0);
                    const std::complex<double> expected = (1 / (81 * sqrt(3 * M_PI))) *
                                                          (27 - (18 * r) + (2 * pow(r, 2))) *
                                                          exp(-r / 3);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }
                }

                SUBCASE("l: 1") {
                  psi.setL(1);

                  SUBCASE("m: -1") {
                    psi.setM(-1);
                    const std::complex<double> expected = (1 / (81. * sqrt(M_PI))) *
                                                          ((6 * r) - pow(r, 2)) * exp(-r / 3) *
                                                          sin(theta) * exp(-i * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 0") {
                    psi.setM(0);
                    const std::complex<double> expected = (1. / 81.) * sqrt(2 / M_PI) *
                                                          ((6 * r) - pow(r, 2)) * exp(-r / 3) *
                                                          cos(theta);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 1") {
                    psi.setM(1);
                    const std::complex<double> expected = (1 / (81 * sqrt(M_PI))) *
                                                          ((6 * r) - pow(r, 2)) * exp(-r / 3) *
                                                          sin(theta) * exp(i * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }
                }

                SUBCASE("l: 2") {
                  psi.setL(2);

                  SUBCASE("m: -2") {
                    psi.setM(-2);
                    const std::complex<double> expected = (1 / (162 * sqrt(M_PI))) * pow(r, 2) *
                                                          exp(-r / 3) * pow(sin(theta), 2) *
                                                          exp(-i * 2. * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: -1") {
                    psi.setM(-1);
                    const std::complex<double> expected = (1 / (81 * sqrt(M_PI))) * pow(r, 2) *
                                                          exp(-r / 3) * sin(theta) * cos(theta) *
                                                          exp(-i * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 0") {
                    psi.setM(0);
                    const std::complex<double> expected = (1 / (81 * sqrt(6 * M_PI))) * pow(r, 2) *
                                                          exp(-r / 3) *
                                                          ((3 * pow(cos(theta), 2)) - 1);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 1") {
                    psi.setM(1);
                    const std::complex<double> expected = (1 / (81 * sqrt(M_PI))) * pow(r, 2) *
                                                          exp(-r / 3) * sin(theta) * cos(theta) *
                                                          exp(i * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }

                  SUBCASE("m: 2") {
                    psi.setM(2);
                    const std::complex<double> expected = (1 / (162 * sqrt(M_PI))) * pow(r, 2) *
                                                          exp(-r / 3) * pow(sin(theta), 2) *
                                                          exp(i * 2. * phi);
                    CHECK_COMPLEX_EQUALS(psi(), expected);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}