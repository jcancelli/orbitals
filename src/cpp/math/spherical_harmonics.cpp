#include "spherical_harmonics.hpp"

#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <cmath>

using boost::math::factorial;

namespace orbitals {

namespace math {

SphericalHarmonics::SphericalHarmonics(int order, int degree)
    : m_Order{order}, m_Degree{degree}, m_Theta{0}, m_Phi{0} {
  updateNormFactor();
  updateThetaFuncValue();
  updatePhiFuncValue();
}

std::complex<double> SphericalHarmonics::operator()() const {
  return m_Value;
}

std::complex<double> SphericalHarmonics::operator()(double theta, double phi) {
  if (theta != m_Theta) {
    setTheta(theta);
  }
  if (phi != m_Phi) {
    setPhi(phi);
  }
  return m_Value;
}

void SphericalHarmonics::setOrder(int order) {
  m_Order = order;
  updateNormFactor();
  updateThetaFuncValue();
  updatePhiFuncValue();
}

void SphericalHarmonics::setDegree(int degree) {
  m_Degree = degree;
  updateNormFactor();
  updateThetaFuncValue();
  updatePhiFuncValue();
}

void SphericalHarmonics::setTheta(double theta) {
  m_Theta = theta;
  updateThetaFuncValue();
}

void SphericalHarmonics::setPhi(double phi) {
  m_Phi = phi;
  updatePhiFuncValue();
}

int SphericalHarmonics::getOrder() const {
  return m_Order;
}

int SphericalHarmonics::getDegree() const {
  return m_Degree;
}

double SphericalHarmonics::getTheta() const {
  return m_Theta;
}

double SphericalHarmonics::getPhi() const {
  return m_Phi;
}

void SphericalHarmonics::updateValue() {
  m_Value = m_normFactor * m_ThetaFuncValue * m_PhiFuncValue;
}

void SphericalHarmonics::updateNormFactor() {
  m_normFactor =
      sqrt(((2. * m_Degree + 1.) / (4. * M_PI)) *
           (factorial<double>(m_Degree - m_Order) / factorial<double>(m_Degree + m_Order)));
  updateValue();
}

void SphericalHarmonics::updateThetaFuncValue() {
  m_ThetaFuncValue = boost::math::legendre_p<double>(m_Degree, m_Order, cos(m_Theta));
  updateValue();
}

void SphericalHarmonics::updatePhiFuncValue() {
  m_PhiFuncValue = exp(m_Order * m_Phi * std::complex<double>(0, 1));
  updateValue();
}

}  // namespace math

}  // namespace orbitals
