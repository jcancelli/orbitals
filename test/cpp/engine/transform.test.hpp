#pragma once

#include "../doctest.h"
#include "../test_util.hpp"
#include "engine/transform.hpp"

using orbitals::engine::Transform;
using orbitals::math::mat4;
using orbitals::math::quatf;
using orbitals::math::vec3;
using orbitals::math::vec4;

TEST_CASE("Testing transforms") {
  Transform t;

  SUBCASE("Testing translation") {
    SUBCASE("setTranslation(x, y, z)") {
      t.setTranslation(3, -22, 11);
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(3, -22, 11, 1));
      t.setTranslation(-1, 5, 56);
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(-1, 5, 56, 1));
    }
    SUBCASE("setTranslation(vec3)") {
      t.setTranslation(vec3(3, -22, 11));
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(3, -22, 11, 1));
      t.setTranslation(vec3(-1, 5, 56));
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(-1, 5, 56, 1));
    }
    SUBCASE("translate(x, y, z)") {
      t.translate(3, -22, 11);
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(3, -22, 11, 1));
      t.translate(-1, 5, 56);
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(2, -17, 67, 1));
    }
    SUBCASE("translate(vec3)") {
      t.translate(vec3(3, -22, 11));
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(3, -22, 11, 1));
      t.translate(vec3(-1, 5, 56));
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 0, 0, 1), vec4(2, -17, 67, 1));
    }
  }

  SUBCASE("Testing rotation") {
    SUBCASE("setRotation(angle, axis)") {
      t.setRotation(M_PI_2, vec3(0, 1, 0));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, -1, 1));
      t.setRotation(M_PI, vec3(0, 1, 0));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(-1, 0, 0, 1));
      t.setRotation(-M_PI_2, vec3(0, 1, 0));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, 1, 1));
      t.setRotation(2 * M_PI + M_PI_2, vec3(0, 1, 0));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, -1, 1));
    }
    SUBCASE("setRotation(quaternion)") {
      t.setRotation(quatf(M_PI_2, vec3(0, 1, 0)));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, -1, 1));
      t.setRotation(quatf(M_PI, vec3(0, 1, 0)));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(-1, 0, 0, 1));
      t.setRotation(quatf(-M_PI_2, vec3(0, 1, 0)));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, 1, 1));
      t.setRotation(quatf(2 * M_PI + M_PI_2, vec3(0, 1, 0)));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, -1, 1));
    }
    SUBCASE("setRotation(x, y, z)") {
      t.setRotation(0, M_PI_2, 0);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, -1, 1));
      t.setRotation(0, M_PI, 0);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(-1, 0, 0, 1));
      t.setRotation(0, -M_PI_2, 0);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, 1, 1));
      t.setRotation(M_PI_2, M_PI_2, 0);
      CHECK_VEC_EQUALS(t.matrix() * vec4(0, 1, 0, 1), vec4(1, 0, 0, 1));
    }
    SUBCASE("rotate(angle, axis)") {
      t.rotate(M_PI_2, vec3(0, 0, 1));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 1, 0, 1));
      t.rotate(M_PI_2, vec3(1, 0, 0));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, 1, 1));
    }
    SUBCASE("rotate(rotation)") {
      t.rotate(quatf(M_PI_2, vec3(0, 0, 1)));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 1, 0, 1));
      t.rotate(quatf(M_PI_2, vec3(1, 0, 0)));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, 1, 1));
    }
    SUBCASE("rotate(x, y, z)") {
      t.rotate(0, 0, M_PI_2);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 1, 0, 1));
      t.rotate(M_PI_2, 0, 0);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 0, 0, 1), vec4(0, 0, 1, 1));
    }
  }

  SUBCASE("Testing scaling") {
    SUBCASE("setScale(x, y, z)") {
      t.setScale(3, 0.5, 11);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 2, 2, 1), vec4(3, 1, 22, 1));
      t.setScale(22, 3, 0.2);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 2, 10, 1), vec4(22, 6, 2, 1));
    }
    SUBCASE("setScale(scale)") {
      t.setScale(vec3(3, 0.5, 11));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 2, 2, 1), vec4(3, 1, 22, 1));
      t.setScale(vec3(22, 3, 0.2));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 2, 10, 1), vec4(22, 6, 2, 1));
    }
    SUBCASE("scale(x, y, z)") {
      t.scale(3, 0.5, 11);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 1, 1, 1), vec4(3, 0.5, 11, 1));
      t.scale(22, 3, 0.2);
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 1, 1, 1), vec4(66, 1.5, 2.2, 1));
    }
    SUBCASE("scale(scale)") {
      t.scale(vec3(3, 0.5, 11));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 1, 1, 1), vec4(3, 0.5, 11, 1));
      t.scale(vec3(22, 3, 0.2));
      CHECK_VEC_EQUALS(t.matrix() * vec4(1, 1, 1, 1), vec4(66, 1.5, 2.2, 1));
    }
  }
}