#pragma once

#include "vector.hpp"

namespace orbitals {

namespace math {

vec3 spherical(float x, float y, float z);
vec3 spherical(vec3 const& cartesian);
vec3 cartesian(float r, float theta, float phi);
vec3 cartesian(vec3 const& spherical);

}  // namespace math

}  // namespace orbitals
