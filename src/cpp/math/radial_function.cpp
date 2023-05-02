#include "radial_function.hpp"

#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>

#include "bohr.hpp"

using boost::math::factorial;

namespace orbitals {

namespace math {

RadialFunction::RadialFunction(unsigned n, unsigned l) : m_N{n}, m_L{l}, m_R{0} {
  assert(l < n && n > 0);
  updateNormFactor();
  updateValue();
}

float RadialFunction::operator()() const {
  return m_Value;
}

float RadialFunction::operator()(float r) {
  if (r != m_R) {
    setR(r);
  }
  return m_Value;
}

void RadialFunction::setN(unsigned n) {
  assert(m_L < n && n > 0);
  m_N = n;
  updateNormFactor();
  updateValue();
}

void RadialFunction::setL(unsigned l) {
  assert(l < m_N);
  m_L = l;
  updateNormFactor();
  updateValue();
}

void RadialFunction::setR(float r) {
  assert(r >= 0);
  m_R = r;
  updateValue();
}

unsigned RadialFunction::getN() const {
  return m_N;
}

unsigned RadialFunction::getL() const {
  return m_L;
}

float RadialFunction::getR() const {
  return m_R;
}

void RadialFunction::updateValue() {
  const float a = (2 * m_R) / (m_N * BOHR_IN_PM);
  m_Value = m_normFactor * exp(-a / 2) * powf(a, m_L) *
            boost::math::laguerre<float>(m_N - m_L - 1, 2 * m_L + 1, a);
}

void RadialFunction::updateNormFactor() {
  const float a = powf(2 / (m_N * BOHR_IN_PM), 3);
  const float b = factorial<float>(m_N - m_L - 1) / (2 * m_N * factorial<float>(m_N + m_L));
  // idk from where that 384.948 comes from, but it manages to normalize the function, so...
  m_normFactor = 384.948f * sqrtf(a * b);
}

}  // namespace math

}  // namespace orbitals
