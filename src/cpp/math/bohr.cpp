#include "bohr.hpp"

namespace orbitals {

namespace math {

double estimateOrbitalRadius(int n) {
  return n * n * BOHR_IN_PM;
}

}  // namespace math

}  // namespace orbitals
