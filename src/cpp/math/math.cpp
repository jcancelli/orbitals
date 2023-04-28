#include "math.hpp"

#include <cassert>

namespace orbitals {

namespace math {

float inversesqrt(float value) {
  assert(value > 0);
  return 1.0f / std::sqrt(value);
}

int factorial(int n) {
  assert(n >= 0);
  if (n == 0) {
    return 1;
  }
  int result = n;
  for (int i = n - 1; i > 0; i--) {
    result *= i;
  }
  return result;
}

}  // namespace math

}  // namespace orbitals