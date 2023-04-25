#include "coordinates.hpp"

#include <cassert>
#include <cmath>

namespace orbitals {

namespace math {

/*
    zenith direction: positive y axis
    inclination: angle [0°-180°] between the positive y axis and the position vector
    azimuth: angle [0°-180°] of rotation around the y axis. 0° is on the positive z axis, 180° is
                on the negative z axis
*/

static float inclination(float x, float y, float z) {
  if (y > 0) {
    return atan(hypot(z, x) / y);
  }
  if (y < 0) {
    return M_PI + atan(hypot(z, x) / y);
  }
  return M_PI_2;
}

static float azimuth(float x, float y, float z) {
  if (z > 0) {
    return atan(x / z);
  }
  if (z < 0) {
    if (x >= 0) {
      return atan(x / z) + M_PI;
    }
    return atan(x / z) - M_PI;
  }
  if (x > 0) {
    return M_PI_2;
  }
  return -M_PI_2;
}

vec3 spherical(float x, float y, float z) {
  assert(z != 0 || x != 0);
  return vec3(                      //
      sqrt(x * x + y * y + z * z),  // r
      inclination(x, y, z),         // inclination
      azimuth(x, y, z)              // azimuth
  );                                //
}

vec3 spherical(vec3 const& cart) {
  return spherical(cart.x(), cart.y(), cart.z());
}

vec3 cartesian(float r, float inclination, float azimuth) {
  return vec3(                              //
      r * cos(azimuth),                     // x
      r * sin(azimuth) * cos(inclination),  // y
      r * sin(azimuth) * sin(inclination)   // z
  );                                        //
}

vec3 cartesian(vec3 const& sphe) {
  return cartesian(sphe[0], sphe[1], sphe[2]);
}

}  // namespace math

}  // namespace orbitals
