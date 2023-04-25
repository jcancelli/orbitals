#pragma once

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/coordinates.hpp"
#include "math/trigonometry.hpp"

using namespace orbitals::math;

TEST_CASE("Testing coordinates") {
  SUBCASE("Testing spherical->cartesian") {
    SUBCASE("Testing (1, 90°, 90°)") {
      vec3 spherCoords(1, M_PI_2, M_PI_2);
      CHECK_VEC_EQUALS(cartesian(spherCoords), vec3(1, 0, 0));
    }
    SUBCASE("Testing (hypot(1, 1), 90°, 45°)") {
      vec3 spherCoords(std::hypot(1.0, 1.0), M_PI_2, M_PI_4);
      CHECK_VEC_EQUALS(cartesian(spherCoords), vec3(1, 0, 1));
    }
    SUBCASE("Testing (sqrt(1+1+1), 54.7356°, 45°)") {
      vec3 spherCoords(std::sqrt(3.f), radians(54.7356f), M_PI_4);
      CHECK_VEC_EQUALS(cartesian(spherCoords), vec3(1, 1, 1));
    }
    SUBCASE("Testing (1, 90°, 270°)") {
      vec3 spherCoords(1, M_PI_2, -M_PI_2);
      CHECK_VEC_EQUALS(cartesian(spherCoords), vec3(-1, 0, 0));
    }
    SUBCASE("Testing (hypot(1, 1), 90°, 225°)") {
      vec3 spherCoords(std::hypot(1.0, 1.0), M_PI_2, -radians(135));
      CHECK_VEC_EQUALS(cartesian(spherCoords), vec3(-1, 0, -1));
    }
    SUBCASE("Testing (1, 90°, 225°)") {
      vec3 spherCoords(std::sqrt(3), radians(125.264f), -radians(135));
      CHECK_VEC_EQUALS(cartesian(spherCoords), vec3(-1, -1, -1));
    }
  }
  SUBCASE("Testing cartesian->spherical") {
    SUBCASE("Testing (1, 0, 0)") {
      vec3 cartCoords(1, 0, 0);
      CHECK_VEC_EQUALS(spherical(cartCoords), vec3(1, M_PI_2, M_PI_2));
    }
    SUBCASE("Testing (1, 0, 1)") {
      vec3 cartCoords(1, 0, 1);
      CHECK_VEC_EQUALS(spherical(cartCoords), vec3(std::hypot(1.0, 1.0), M_PI_2, M_PI_4));
    }
    SUBCASE("Testing (1, 1, 1)") {
      vec3 cartCoords(1, 1, 1);
      CHECK_VEC_EQUALS(spherical(cartCoords), vec3(std::sqrt(3), radians(54.7356f), M_PI_4));
    }
    SUBCASE("Testing (-1, 0, 0)") {
      vec3 cartCoords(-1, 0, 0);
      CHECK_VEC_EQUALS(spherical(cartCoords), vec3(1, M_PI_2, -M_PI_2));
    }
    SUBCASE("Testing (-1, 0, -1)") {
      vec3 cartCoords(-1, 0, -1);
      CHECK_VEC_EQUALS(spherical(cartCoords), vec3(std::hypot(1.0, 1.0), M_PI_2, -radians(135)));
    }
    SUBCASE("Testing (-1, -1, -1)") {
      vec3 cartCoords(-1, -1, -1);
      CHECK_VEC_EQUALS(spherical(cartCoords), vec3(std::sqrt(3), radians(125.264f), -radians(135)));
    }
  }
}