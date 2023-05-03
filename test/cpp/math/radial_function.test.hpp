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

  for (float r = 0; r <= 4; r += 0.25) {
    R.setR(BOHR_TO_PM(r));
    SUBCASE(("r: "s + std::to_string(r) + " bohrs").c_str()) {
      SUBCASE("n: 1") {
        R.setN(1);

        SUBCASE("l: 0") {
          R.setL(0);
          const float expected = 2.f * expf(-r);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }
      }

      SUBCASE("n: 2") {
        R.setN(2);

        SUBCASE("l: 0") {
          R.setL(0);
          const float expected = (1 / sqrtf(2)) * (1 - (r / 2)) * expf(-r / 2);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }

        SUBCASE("l: 1") {
          R.setL(1);
          const float expected = (1 / sqrtf(24)) * r * expf(-r / 2);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }
      }

      SUBCASE("n: 3") {
        R.setN(3);

        SUBCASE("l: 0") {
          R.setL(0);
          const float expected =
              (2 / sqrtf(27)) * (1 - ((2 * r) / 3) + ((2 * powf(r, 2)) / 27)) * expf(-r / 3);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }

        SUBCASE("l: 1") {
          R.setL(1);
          const float expected = (8 / (27 * sqrtf(6))) * r * (1 - (r / 6)) * expf(-r / 3);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }

        SUBCASE("l: 2") {
          R.setL(2);
          const float expected = (4 / (81 * sqrtf(30))) * powf(r, 2) * expf(-r / 3);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }
      }

      SUBCASE("n: 4") {
        R.setN(4);

        const float roh = r / 2;

        SUBCASE("l: 0") {
          R.setL(0);
          const float expected =
              (1.f / 96.f) * (24 - 36 * roh + 12 * powf(roh, 2) - powf(roh, 3)) * expf(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }

        SUBCASE("l: 1") {
          R.setL(1);
          const float expected =
              (1 / (32 * sqrtf(15))) * (20 - 10 * roh + powf(roh, 2)) * roh * expf(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }

        SUBCASE("l: 2") {
          R.setL(2);
          const float expected = (1 / (96 * sqrtf(5))) * (6 - roh) * powf(roh, 2) * expf(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }

        SUBCASE("l: 3") {
          R.setL(3);
          const float expected = (1 / (96 * sqrtf(35))) * powf(roh, 3) * expf(-r / 4);
          CHECK(R() == doctest::Approx(expected).epsilon(.000001));
        }
      }
    }
  }
}