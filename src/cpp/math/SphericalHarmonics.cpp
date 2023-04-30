#include "SphericalHarmonics.hpp"

#include <boost/math/special_functions/legendre.hpp>
#include <cmath>

#include "math.hpp"

namespace orbitals {

namespace math {

SphericalHarmonics::SphericalHarmonics(int order, int degree) : m_Order{order}, m_Degree{degree} {
  updateNormFactor();
}

std::complex<float> SphericalHarmonics::operator()(float theta, float phi) const {
  return m_normFactor * exp(m_Order * phi * std::complex<float>(0, 1)) *
         boost::math::legendre_p(m_Degree, m_Order, cosf(theta));
}

void SphericalHarmonics::setOrder(int order) {
  m_Order = order;
  updateNormFactor();
}

void SphericalHarmonics::setDegree(int degree) {
  m_Degree = degree;
  updateNormFactor();
}

int SphericalHarmonics::getOrder() const {
  return m_Order;
}

int SphericalHarmonics::getDegree() const {
  return m_Degree;
}

void SphericalHarmonics::updateNormFactor() {
  m_normFactor = sqrt(((2 * m_Degree + 1) / (4 * M_PI)) *
                      (factorial(m_Degree - m_Order) / factorial(m_Degree + m_Order)));
}

}  // namespace math

}  // namespace orbitals
