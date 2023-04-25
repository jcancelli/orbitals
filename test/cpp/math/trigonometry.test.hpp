#pragma once

#include <iostream>

#include "../doctest.h"
#include "math/trigonometry.hpp"

using namespace orbitals::math;

TEST_CASE("Testing trigonometry functions") {
  SUBCASE("degrees->radians") {
    CHECK(radians(45) == doctest::Approx(M_PI / 4));
    CHECK(radians(90) == doctest::Approx(M_PI / 2));
    CHECK(radians(180) == doctest::Approx(M_PI));
    CHECK(radians(405) == doctest::Approx(M_PI / 4 + 2 * M_PI));
    CHECK(radians(-90) == doctest::Approx(-M_PI / 2));
  }
  SUBCASE("radians->degrees") {
    CHECK(degrees(M_PI / 4) == doctest::Approx(45));
    CHECK(degrees(M_PI / 2) == doctest::Approx(90));
    CHECK(degrees(M_PI) == doctest::Approx(180));
    CHECK(degrees(M_PI / 4 + 2 * M_PI) == doctest::Approx(405));
    CHECK(degrees(-M_PI / 2) == doctest::Approx(-90));
  }
}