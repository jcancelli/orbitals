#pragma once

#include "../doctest.h"
#include "math/trigonometry.hpp"

using namespace orbitals::math;

TEST_CASE("Testing trigonometry functions") {
  SUBCASE("degrees->radians") {
    CHECK(radians(45) == doctest::Approx(M_PI / 4).epsilon(.00000000000001));
    CHECK(radians(90) == doctest::Approx(M_PI / 2).epsilon(.00000000000001));
    CHECK(radians(180) == doctest::Approx(M_PI).epsilon(.00000000000001));
    CHECK(radians(405) == doctest::Approx(M_PI / 4 + 2 * M_PI).epsilon(.00000000000001));
    CHECK(radians(-90) == doctest::Approx(-M_PI / 2).epsilon(.00000000000001));
  }
  SUBCASE("radians->degrees") {
    CHECK(degrees(M_PI / 4) == doctest::Approx(45).epsilon(.00000000000001));
    CHECK(degrees(M_PI / 2) == doctest::Approx(90).epsilon(.00000000000001));
    CHECK(degrees(M_PI) == doctest::Approx(180).epsilon(.00000000000001));
    CHECK(degrees(M_PI / 4 + 2 * M_PI) == doctest::Approx(405).epsilon(.00000000000001));
    CHECK(degrees(-M_PI / 2) == doctest::Approx(-90).epsilon(.00000000000001));
  }
}