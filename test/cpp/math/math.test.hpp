#pragma once

#include "../doctest.h"
#include "math/math.hpp"

using namespace orbitals::math;

TEST_CASE("Testing math") {
  SUBCASE("Testing inversesqrt") {
    CHECK(inversesqrt(1) == 1);
    CHECK(inversesqrt(4) == 0.5);
    CHECK(inversesqrt(3.3) == doctest::Approx(0.5504818f));
  }

  SUBCASE("Testing factorial") {
    CHECK(factorial(0) == 1);
    CHECK(factorial(1) == 1);
    CHECK(factorial(2) == 2);
    CHECK(factorial(3) == 6);
    CHECK(factorial(4) == 24);
    CHECK(factorial(5) == 120);
  }
}