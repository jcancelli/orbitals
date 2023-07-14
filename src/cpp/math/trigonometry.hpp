#pragma once

#include <type_traits>

#include "vector.hpp"

namespace orbitals {

namespace math {

double const ONE_DEGREE_IN_RAD = 0.01745329251994329576923690768489;
double const ONE_RADIAN_IN_DEG = 57.295779513082320876798154814105;

double radians(double deg);
double degrees(double rad);

}  // namespace math

}  // namespace orbitals