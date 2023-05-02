#pragma once

#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>

#include "../doctest.h"
#include "math/RadialFunction.hpp"
#include "math/bohr.hpp"

using namespace orbitals::math;

TEST_CASE("Testing radial function") {
  RadialFunction R(1, 0);
  const float r_pm = BOHR_TO_PM(2);
  const float r_bohr = PM_TO_BOHR(r_pm);
  const float norm = powf(1, -3 / 2);

  SUBCASE("n: 1") {
    R.setN(1);
    SUBCASE("l: 0") {
      R.setL(0);
      CHECK(R(r_pm) == doctest::Approx(2 * expf(-r_bohr)).epsilon(.000001));
    }
  }

  SUBCASE("n: 2") {
    R.setN(2);

    SUBCASE("l: 0") {
      R.setL(0);
      CHECK(R(r_pm) == doctest::Approx((1 / sqrtf(2)) * (1 - 0.5 * r_bohr) * expf(-r_bohr / 2))
                           .epsilon(.000001));
    }

    SUBCASE("l: 1") {
      R.setL(1);
      CHECK(R(r_pm) ==
            doctest::Approx((1 / sqrtf(24)) * r_bohr * expf(-r_bohr / 2)).epsilon(.000001));
    }
  }

  SUBCASE("n: 3") {
    R.setN(3);

    SUBCASE("l: 0") {
      R.setL(0);
      CHECK(R(r_pm) == doctest::Approx((2 / sqrtf(27)) *
                                       (1 - ((2 * r_bohr) / (3 * 1)) +
                                        ((2 * powf(r_bohr, 2)) / (27 * powf(1, 2)))) *
                                       expf(-r_bohr / 3))
                           .epsilon(.000001));
    }

    SUBCASE("l: 1") {
      R.setL(1);
      CHECK(R(r_pm) ==
            doctest::Approx((8 / (27 * sqrtf(6))) * (1 - (r_bohr / 6)) * r_bohr * expf(-r_bohr / 3))
                .epsilon(.000001));
    }
  }
}