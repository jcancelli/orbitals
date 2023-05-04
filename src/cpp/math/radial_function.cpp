#include "radial_function.hpp"

#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/laguerre.hpp>
#include <cmath>

#include "bohr.hpp"

using boost::math::factorial;

namespace orbitals {

namespace math {

RadialFunction::RadialFunction() : m_N{1}, m_L{0}, m_R{0} {
  updateNormFactor();
  updateValue();
}

RadialFunction::RadialFunction(unsigned n, unsigned l) : m_N{n}, m_L{l}, m_R{0} {
  assert(l < n && n > 0);
  updateNormFactor();
  updateValue();
}

double RadialFunction::operator()() const {
  return m_Value;
}

double RadialFunction::operator()(double r) {
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

void RadialFunction::setR(double r) {
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

double RadialFunction::getR() const {
  return m_R;
}

void RadialFunction::updateValue() {
  const double a = (2 * m_R) / (m_N * BOHR_IN_PM);
  m_Value = m_normFactor * exp(-a / 2) * pow(a, m_L) *
            boost::math::laguerre<double>(m_N - m_L - 1, 2 * m_L + 1, a);
}

void RadialFunction::updateNormFactor() {
  const double a = pow(2 / (m_N * BOHR_IN_PM), 3);
  const double b = factorial<double>(m_N - m_L - 1) / (2 * m_N * factorial<double>(m_N + m_L));
  // idk from where that 384.948 comes from, but it manages to normalize the function, so...
  m_normFactor = 384.948 * sqrt(a * b);
}

}  // namespace math

}  // namespace orbitals
