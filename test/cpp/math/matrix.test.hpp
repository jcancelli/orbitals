#pragma once

#include "../doctest.h"
#include "../test_util.hpp"
#include "math/matrix.hpp"
#include "math/quaternion.hpp"

using namespace orbitals::math;

static inline mat4 make_matrix(float data[4][4]) {
  mat4 m;
  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      m[col][row] = data[row][col];
    }
  }
  return m;
}

TEST_CASE("Testing mat4") {
  SUBCASE("Testing constructors") {
    SUBCASE("Copy constructor") {
      CHECK(mat4(mat4(5)) == mat4(5));
    }
    SUBCASE("From quaternion") {
      CHECK_VEC_EQUALS(mat4(quatf(M_PI_2, vec3(0, 1, 0))) * vec4(1, 0, 0, 1), vec4(0, 0, -1, 1));
    }
  }

  SUBCASE("Testing operators") {
    mat4 m1 = make_matrix((float[4][4]){{11.f, 12.f, 13.f, 14.f},
                                        {15.f, 16.f, 17.f, 18.f},
                                        {19.f, 10.f, 11.f, 12.f},
                                        {13.f, 14.f, 15.f, 16.f}});
    mat4 m2 = make_matrix((float[4][4]){{21.f, 22.f, 23.f, 24.f},
                                        {25.f, 26.f, 27.f, 28.f},
                                        {29.f, 20.f, 21.f, 22.f},
                                        {23.f, 24.f, 25.f, 26.f}});

    SUBCASE("arithmetic operators") {
      CHECK(m1 + m2 == make_matrix((float[4][4]){{32.f, 34.f, 36.f, 38.f},
                                                 {40.f, 42.f, 44.f, 46.f},
                                                 {48.f, 30.f, 32.f, 34.f},
                                                 {36.f, 38.f, 40.f, 42.f}}));
      CHECK(m1 - m2 == make_matrix((float[4][4]){{-10.f, -10.f, -10.f, -10.f},
                                                 {-10.f, -10.f, -10.f, -10.f},
                                                 {-10.f, -10.f, -10.f, -10.f},
                                                 {-10.f, -10.f, -10.f, -10.f}}));
      CHECK(m1 * m2 == make_matrix((float[4][4]){{1230.f, 1150.f, 1200.f, 1250.f},
                                                 {1622.f, 1518.f, 1584.f, 1650.f},
                                                 {1244.f, 1186.f, 1238.f, 1290.f},
                                                 {1426.f, 1334.f, 1392.f, 1450.f}}));
      CHECK(m1 * vec4(1, 2, 3, 4) == vec4(130, 170, 120, 150));
      CHECK(vec4(1, 2, 3, 4) * m1 == vec4(150, 130, 140, 150));
      CHECK(m1 * 2 == make_matrix((float[4][4]){{22.f, 24.f, 26.f, 28.f},
                                                {30.f, 32.f, 34.f, 36.f},
                                                {38.f, 20.f, 22.f, 24.f},
                                                {26.f, 28.f, 30.f, 32.f}}));
      CHECK(2 * m1 == make_matrix((float[4][4]){{22.f, 24.f, 26.f, 28.f},
                                                {30.f, 32.f, 34.f, 36.f},
                                                {38.f, 20.f, 22.f, 24.f},
                                                {26.f, 28.f, 30.f, 32.f}}));
    }

    SUBCASE("operator=") {
      m1 = m2;
      CHECK(m1 == m2);
    }
    SUBCASE("operator+=") {
      m1 += m2;
      CHECK(m1 == make_matrix((float[4][4]){{32.f, 34.f, 36.f, 38.f},
                                            {40.f, 42.f, 44.f, 46.f},
                                            {48.f, 30.f, 32.f, 34.f},
                                            {36.f, 38.f, 40.f, 42.f}}));
    }
    SUBCASE("operator-=") {
      m1 -= m2;
      CHECK(m1 == make_matrix((float[4][4]){{-10.f, -10.f, -10.f, -10.f},
                                            {-10.f, -10.f, -10.f, -10.f},
                                            {-10.f, -10.f, -10.f, -10.f},
                                            {-10.f, -10.f, -10.f, -10.f}}));
    }
    SUBCASE("operator*=") {
      m1 *= 2;
      CHECK(m1 == make_matrix((float[4][4]){{22.f, 24.f, 26.f, 28.f},
                                            {30.f, 32.f, 34.f, 36.f},
                                            {38.f, 20.f, 22.f, 24.f},
                                            {26.f, 28.f, 30.f, 32.f}}));
    }

    SUBCASE("Comparison operators") {
      CHECK(m1 == m1);        // ==
      CHECK(m1 == mat4(m1));  // ==
      CHECK(m1 != m2);        // !=
    }

    SUBCASE("operator[]") {
      m1[0][0] = 1000;
      m1[1][0] = 100;
      m1[2][0] = 10;
      m1[3][0] = 1;
      CHECK(m1 == make_matrix((float[4][4]){{1000.f, 100.f, 10.f, 1.f},
                                            {15.f, 16.f, 17.f, 18.f},
                                            {19.f, 10.f, 11.f, 12.f},
                                            {13.f, 14.f, 15.f, 16.f}}));
    }

    SUBCASE("operator()") {
      m1(0, 0) = 1000;
      m1(1, 0) = 100;
      m1(2, 0) = 10;
      m1(3, 0) = 1;
      CHECK(m1 == make_matrix((float[4][4]){{1000.f, 100.f, 10.f, 1.f},
                                            {15.f, 16.f, 17.f, 18.f},
                                            {19.f, 10.f, 11.f, 12.f},
                                            {13.f, 14.f, 15.f, 16.f}}));
    }
  }

  SUBCASE("Testing methods") {
    mat4 m1 = make_matrix((float[4][4]){{11.f, 12.f, 13.f, 14.f},
                                        {21.f, 22.f, 23.f, 24.f},
                                        {31.f, 32.f, 33.f, 34.f},
                                        {41.f, 42.f, 43.f, 44.f}});
    SUBCASE("data") {
      float* data = m1.data();
      for (int col = 0; col < 4; col++) {
        for (int row = 0; row < 4; row++, data++) {
          CHECK(*data == m1[col][row]);
        }
      }
    }

    SUBCASE("rows and columns") {
      CHECK(m1.rows() == 4);
      CHECK(m1.columns() == 4);
    }

    SUBCASE("translate") {
      mat4 m1(1);
      mat4 m2(1);
      m1.translate(1, 2, 3);
      m2.translate(vec3(1, 2, 3));
      CHECK(m1 == m2);
      CHECK_VEC_EQUALS(m1 * vec4(1, 2, 3, 1), vec4(2, 4, 6, 1));
    }
    SUBCASE("translated") {
      mat4 m1(1);
      mat4 m2(1);
      CHECK(m1.translated(1, 2, 3) == m2.translated(vec3(1, 2, 3)));
      CHECK(m1.translated(1, 2, 3) * vec4(1, 2, 3, 1) == vec4(2, 4, 6, 1));
    }

    SUBCASE("rotate") {
      mat4 m(1);
      m.rotate(M_PI / 2, vec3(0, 1, 0));
      vec4 rotatedVector = m * vec4(1, 0, 0, 1);
      CHECK_VEC_EQUALS(rotatedVector, vec4(0, 0, -1, 1));
    }
    SUBCASE("rotated") {
      mat4 m(1);
      vec4 rotatedVector = m.rotated(M_PI / 2, vec3(0, 1, 0)) * vec4(1, 0, 0, 1);
      CHECK_VEC_EQUALS(rotatedVector, vec4(0, 0, -1, 1));
    }

    SUBCASE("scale") {
      mat4 m1(1);
      mat4 m2(1);
      m1.scale(1, 2, 3);
      m2.scale(vec3(1, 2, 3));
      CHECK(m1 == m2);
      CHECK_VEC_EQUALS(m1 * vec4(1, 2, 3, 1), vec4(1, 4, 9, 1));
    }
    SUBCASE("scaled") {
      mat4 m1(1);
      mat4 m2(1);
      CHECK(m1.scaled(1, 2, 3) == m2.scaled(vec3(1, 2, 3)));
      CHECK(m1.scaled(1, 2, 3) * vec4(1, 2, 3, 1) == vec4(1, 4, 9, 1));
    }
  }
}