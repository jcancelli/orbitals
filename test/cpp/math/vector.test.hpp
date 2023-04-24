#include "../doctest.h"
#include "math/vector.hpp"

using namespace orbitals::math;

TEST_CASE("Testing vec3") {
  SUBCASE("Testing constructors") {
    CHECK(vec3() == vec3(0, 0, 0));
    CHECK(vec3(3) == vec3(3, 3, 3));
    CHECK(vec3(vec3(1, 2, 3)) == vec3(1, 2, 3));
  }

  SUBCASE("Testing operators") {
    vec3 v1(2, 2, 2);
    vec3 v2(3, 3, 3);

    SUBCASE("arithmetic operators") {
      CHECK(v1 + v2 == vec3(5, 5, 5));                         // +
      CHECK(v1 - v2 == vec3(-1, -1, -1));                      // -
      CHECK(v1 * 3.f == vec3(6, 6, 6));                        // vec * scalar
      CHECK(v1 * 3 == vec3(6, 6, 6));                          // vec * scalar
      CHECK(v1 * 0 == vec3(0, 0, 0));                          // vec * scalar
      CHECK(3.f * v1 == vec3(6, 6, 6));                        // scalar * vec
      CHECK(3 * v1 == vec3(6, 6, 6));                          // scalar * vec
      CHECK(0 * v1 == vec3(0, 0, 0));                          // scalar * vec
      CHECK(v1 / 3 == vec3(2.f / 3.f, 2.f / 3.f, 2.f / 3.f));  // vec / scalar
    }

    SUBCASE("operator=") {
      v1 = vec3(32, 32, 32);
      CHECK(v1 == vec3(32, 32, 32));
    }
    SUBCASE("operator+=") {
      v1 += v2;
      CHECK(v1 == vec3(5, 5, 5));
    }
    SUBCASE("operator-=") {
      v1 -= v2;
      CHECK(v1 == vec3(-1, -1, -1));
    }
    SUBCASE("operator*=") {
      v1 *= 3;
      CHECK(v1 == vec3(6, 6, 6));
    }
    SUBCASE("operator/=") {
      v1 /= 3;
      CHECK(v1 == vec3(2.f / 3.f, 2.f / 3.f, 2.f / 3.f));
    }

    SUBCASE("Comparison operators") {
      CHECK(v1 == v1);        // ==
      CHECK(v1 == vec3(v1));  // ==
      CHECK(v1 != v2);        // !=
    }

    SUBCASE("operator[]") {
      v1[0] = 123;
      v1[1] = 456;
      v1[2] = 789;
      CHECK(v1 == vec3(123, 456, 789));
    }

    SUBCASE("operator()") {
      v1(30, 40, 50);
      CHECK(v1 == vec3(30, 40, 50));
    }
  }

  SUBCASE("Testing methods") {
    vec3 v1(1, 2, 3);
    vec3 v2(4, 5, 6);

    SUBCASE("data") {
      float* data = v1.data();
      for (int i = 0; i < 3; i++, data++) {
        CHECK(*data == v1[i]);
      }
    }

    SUBCASE("dot") {
      CHECK(v1.dot(v2) == 32);
    }

    SUBCASE("normalize") {
      vec3 copy = v1;
      copy.normalize();
      CHECK(copy.length() == doctest::Approx(1));
      CHECK(copy == v1 / v1.length());
    }

    SUBCASE("normalized") {
      CHECK(v1.normalized().length() == doctest::Approx(1));
      CHECK(v1.normalized() == v1 / v1.length());
    }

    SUBCASE("reflected") {
      CHECK(v1.reflected(v2) == vec3(-255, -318, -381));
    }

    SUBCASE("length") {
      CHECK(v1.length() == doctest::Approx(3.741657));
    }

    SUBCASE("distance") {
      CHECK(v1.distance(v2) == doctest::Approx(5.196152));
      CHECK(vec3(-123, -2, 78).distance(v2) == doctest::Approx(146.1575));
    }

    SUBCASE("size") {
      CHECK(v1.size() == 3);
    }

    SUBCASE("x, y, z") {
      CHECK(v1.x() == v1[0]);
      CHECK(v1.y() == v1[1]);
      CHECK(v1.z() == v1[2]);
      SUBCASE("x, y, z") {
        v1.x() = 321;
        v1.y() = 987;
        v1.z() = 654;
        CHECK(v1 == vec3(321, 987, 654));
      }
    }

    SUBCASE("cross") {
      CHECK(v1.cross(v2) == vec3(-3, 6, -3));
    }
  }
}