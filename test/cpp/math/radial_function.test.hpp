#pragma once

#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>
#include <string>

#include "../doctest.h"
#include "math/bohr.hpp"
#include "math/radial_function.hpp"

using namespace orbitals::math;
using namespace std::string_literals;

// source_1: https://research.csiro.au/static/dcm/HydrogenAtomWaveFunction.htm
// source_2: https://folk.uib.no/nfylk/PHYS261/2016_09_01/0020_Psi_hydrogen_citizendum.png
TEST_CASE("Testing radial function") {
  RadialFunction R;

  for (double r = 0; r <= 4; r += 0.25) {
    R.setR(BOHR_TO_PM(r));
    SUBCASE(("r: "s + std::to_string(r) + " bohrs").c_str()) {
      SUBCASE("n: 1") {
        R.setN(1);

        SUBCASE("l: 0") {
          R.setL(0);
          const double expected = 2. * exp(-r);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }
      }

      SUBCASE("n: 2") {
        R.setN(2);

        SUBCASE("l: 0") {
          R.setL(0);
          const double expected = (1 / sqrt(2)) * (1 - (r / 2)) * exp(-r / 2);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }

        SUBCASE("l: 1") {
          R.setL(1);
          const double expected = (1 / sqrt(24)) * r * exp(-r / 2);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }
      }

      SUBCASE("n: 3") {
        R.setN(3);

        SUBCASE("l: 0") {
          R.setL(0);
          const double expected =
              (2 / sqrt(27)) * (1 - ((2 * r) / 3) + ((2 * pow(r, 2)) / 27)) * exp(-r / 3);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }

        SUBCASE("l: 1") {
          R.setL(1);
          const double expected = (8 / (27 * sqrt(6))) * r * (1 - (r / 6)) * exp(-r / 3);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }

        SUBCASE("l: 2") {
          R.setL(2);
          const double expected = (4 / (81 * sqrt(30))) * pow(r, 2) * exp(-r / 3);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }
      }

      SUBCASE("n: 4") {
        R.setN(4);

        const double roh = r / 2;

        SUBCASE("l: 0") {
          R.setL(0);
          const double expected =
              (1. / 96.) * (24 - 36 * roh + 12 * pow(roh, 2) - pow(roh, 3)) * exp(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }

        SUBCASE("l: 1") {
          R.setL(1);
          const double expected =
              (1 / (32 * sqrt(15))) * (20 - 10 * roh + pow(roh, 2)) * roh * exp(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }

        SUBCASE("l: 2") {
          R.setL(2);
          const double expected = (1 / (96 * sqrt(5))) * (6 - roh) * pow(roh, 2) * exp(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }

        SUBCASE("l: 3") {
          R.setL(3);
          const double expected = (1 / (96 * sqrt(35))) * pow(roh, 3) * exp(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
          CHECK_SIGN_EQUALS(R(), expected);
        }
      }
    }
  }
}