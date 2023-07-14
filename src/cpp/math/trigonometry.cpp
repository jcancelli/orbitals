#include "trigonometry.hpp"

namespace orbitals {

namespace math {

double radians(double deg) {
  return deg * ONE_DEGREE_IN_RAD;
}

double degrees(double rad) {
  return rad * ONE_RADIAN_IN_DEG;
}

}  // namespace math

}  // namespace orbitals