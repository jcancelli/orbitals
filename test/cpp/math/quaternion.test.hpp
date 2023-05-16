#pragma once

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/quaternion.hpp"

using namespace orbitals::math;

TEST_CASE("Testing quaternion") {
  SUBCASE("Testing constructors") {
    SUBCASE("quat<T>()") {
      quatf a;
      CHECK(a.x == 0);
      CHECK(a.y == 0);
      CHECK(a.z == 0);
      CHECK(a.w == 0);
    }
    SUBCASE("quat<T>(T,T,T,T)") {
      quatf a(1, 2, 3, 4);
      CHECK(a.x == 1);
      CHECK(a.y == 2);
      CHECK(a.z == 3);
      CHECK(a.w == 4);
    }
    SUBCASE("quat<T>(quat<T>&)") {
      quatf a(1, 2, 3, 4);
      quatf b(a);
      CHECK(b.x == 1);
      CHECK(b.y == 2);
      CHECK(b.z == 3);
      CHECK(b.w == 4);
    }
    SUBCASE("quat<T>(T, generic_vec3<T>)") {
      quatf a(M_PI, vec3(0, 1, 0));
      CHECK(a.x == 0);
      CHECK(a.y == 1);
      CHECK(a.z == 0);
      CHECK(a.w == doctest::Approx(M_PI).epsilon(.00001));
    }
    // SUBCASE("quat<T>(generic_vec3<T>)") {
    //   quatf a(M_PI, vec3(0, 1, 0));
    //   CHECK(a.x == 0);
    //   CHECK(a.y == 0);
    //   CHECK(a.z == 0);
    //   CHECK(a.w == 0);
    // }
  }
  SUBCASE("Testing methods") {
    quatf a(1, 2, 3, 4);
    quatf b(4, 3, 2, 1);

    SUBCASE("conjugate") {
      CHECK_QUAT_EQUALS(a.conjugate(), quatf(-1, -2, -3, 4));
    }
    SUBCASE("inverse") {
      CHECK_QUAT_EQUALS(a.inverse(), quatf(-0.0333333, -0.0666667, -0.1, 0.1333333));
    }
    SUBCASE("normalized") {
      CHECK_QUAT_EQUALS(a.normalized(), quatf(0.1825742, 0.3651484, 0.5477226, 0.7302967));
    }
    SUBCASE("dot") {
      CHECK(a.dot(b) == 20);
    }
    SUBCASE("length") {
      CHECK(a.length() == doctest::Approx(std::sqrt(30)).epsilon(.000001));
    }
  }

  SUBCASE("Testing operators") {
    quatf a(1, 2, 3, 4);
    quatf b(4, 3, 2, 1);

    SUBCASE("quat + quat") {
      CHECK_QUAT_EQUALS(a + b, quatf(5, 5, 5, 5));
    }
    SUBCASE("quat - quat") {
      CHECK_QUAT_EQUALS(a - b, quatf(-3, -1, 1, 3));
    }
    SUBCASE("quat * quat") {
      CHECK_QUAT_EQUALS(a * b, quatf(12, 24, 6, -12));
    }
    SUBCASE("quat * vec3") {
      CHECK_VEC_EQUALS(a * vec3(3, 2, 1), vec3(-93, 50, 1));
    }
    SUBCASE("vec3 * quat") {
      CHECK_VEC_EQUALS(vec3(3, 2, 1) * a, vec3(2.96444, 1.91111, 1.07111));
    }
    SUBCASE("quat * scalar") {
      CHECK_QUAT_EQUALS(a * 2, quatf(2, 4, 6, 8));
    }
    SUBCASE("scalar * quat") {
      CHECK_QUAT_EQUALS(2.f * a, quatf(2, 4, 6, 8));
    }
    SUBCASE("quat / scalar") {
      CHECK_QUAT_EQUALS(a / 2, quatf(0.5, 1, 1.5, 2));
    }
    SUBCASE("operator =") {
      a = b;
      CHECK_QUAT_EQUALS(a, b);
    }
    SUBCASE("+= quat") {
      a += b;
      CHECK_QUAT_EQUALS(a, quatf(5, 5, 5, 5));
    }
    SUBCASE("-= quat") {
      a -= b;
      CHECK_QUAT_EQUALS(a, quatf(-3, -1, 1, 3));
    }
    SUBCASE("*= quat") {
      a *= b;
      CHECK_QUAT_EQUALS(a, quatf(12, 24, 6, -12));
    }
    SUBCASE("operator ==") {
      CHECK(!(a == b));
      CHECK(a == quatf(1, 2, 3, 4));
    }
    SUBCASE("operator !=") {
      CHECK(a != b);
      CHECK(!(a != quatf(1, 2, 3, 4)));
    }
    SUBCASE("operator []") {
      CHECK(a[0] == 1);
      CHECK(a[1] == 2);
      CHECK(a[2] == 3);
      CHECK(a[3] == 4);
    }
  }
}