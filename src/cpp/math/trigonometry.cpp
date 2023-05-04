#include "trigonometry.hpp"

namespace orbitals {

namespace math {

double radians(double deg) {
  return deg * 0.01745329251994329576923690768489;
}

double degrees(double rad) {
  return rad * 57.295779513082320876798154814105;
}

}  // namespace math

}  // namespace orbitals