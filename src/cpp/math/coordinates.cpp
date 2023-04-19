#include "coordinates.hpp"

#include <cassert>
#include <cmath>

namespace orbitals {

namespace math {

vec3 spherical(float x, float y, float z) {
  assert(x != 0 || y != 0);
  const float r = sqrt(x * x + y * y + z * z);
  return vec3(                                     //
      r,                                           //
      acos(z / r),                                 //
      ((y > 0) - (y < 0)) * acos(x / hypot(x, y))  //
  );                                               //
}

vec3 spherical(vec3 const& cart) {
  return spherical(cart.x(), cart.y(), cart.z());
}

vec3 cartesian(float r, float theta, float phi) {
  return vec3(                    //
      r * sin(phi) * cos(theta),  //
      r * sin(phi) * sin(theta),  //
      r * cos(phi)                //
  );                              //
}

vec3 cartesian(vec3 const& sphe) {
  return cartesian(sphe[0], sphe[1], sphe[2]);
}

}  // namespace math

}  // namespace orbitals
