#include "RadialFunction.hpp"

#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>

#include "bohr.hpp"

using boost::math::factorial;

namespace orbitals {

namespace math {

RadialFunction::RadialFunction(unsigned n, unsigned l) : m_N{n}, m_L{l} {
  assert(l < n && n > 0);
  updateNormFactor();
}

float RadialFunction::operator()(float r) const {
  const float a = (2 * r) / (m_N * BOHR_IN_PM);
  return m_normFactor * exp(-a / 2) * powf(a, m_L) *
         boost::math::laguerre<float>(m_N - m_L - 1, 2 * m_L + 1, a);
}

void RadialFunction::setN(unsigned n) {
  assert(m_L < n && n > 0);
  m_N = n;
  updateNormFactor();
}

void RadialFunction::setL(unsigned l) {
  assert(l < m_N);
  m_L = l;
  updateNormFactor();
}

unsigned RadialFunction::getN() const {
  return m_N;
}

unsigned RadialFunction::getL() const {
  return m_L;
}

void RadialFunction::updateNormFactor() {
  const float a = powf(2 / (m_N * BOHR_IN_PM), 3);
  const float b = factorial<float>(m_N - m_L - 1) / (2 * m_N * factorial<float>(m_N + m_L));
  // idk from where that 384.948 comes from, but it manages to normalize the function, so...
  m_normFactor = 384.948f * sqrtf(a * b);
}

}  // namespace math

}  // namespace orbitals
