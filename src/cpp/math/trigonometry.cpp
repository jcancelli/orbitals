#include "trigonometry.hpp"

namespace orbitals {

namespace math {

float radians(float deg) {
  return deg * 0.01745329251994329576923690768489;
}

float degrees(float rad) {
  return rad * 57.295779513082320876798154814105;
}

}  // namespace math

}  // namespace orbitals