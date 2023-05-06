#include "wave_function.hpp"

#include <boost/math/special_functions/spherical_harmonic.hpp>
#include <cassert>
#include <cmath>
#include <iostream>

namespace orbitals {

namespace math {

WaveFunction::WaveFunction() : m_Radial(1, 0), m_Angular(0, 0) {
  updateValue();
}

WaveFunction::WaveFunction(unsigned n, unsigned l, int m) : m_Radial(n, l), m_Angular(m, l) {
  updateValue();
}

std::complex<double> WaveFunction::operator()() const {
  return m_Value;
}

std::complex<double> WaveFunction::operator()(double r, double theta, double phi) {
  if (r != getR()) {
    setR(r);
  }
  if (theta != getTheta()) {
    setTheta(r);
  }
  if (phi != getPhi()) {
    setPhi(r);
  }
  return m_Value;
}

void WaveFunction::setN(unsigned n) {
  assert(n > 0);
  m_Radial.setN(n);
  updateValue();
}

void WaveFunction::setL(unsigned l) {
  assert(l < getN());
  m_Radial.setL(l);
  m_Angular.setDegree(l);
  updateValue();
}

void WaveFunction::setM(int m) {
  assert(m >= -int(getL()) && m <= int(getL()));
  m_Angular.setOrder(m);
  updateValue();
}

void WaveFunction::setR(double r) {
  assert(r >= 0);
  m_Radial.setR(r);
  updateValue();
}

void WaveFunction::setTheta(double theta) {
  m_Angular.setTheta(theta);
  updateValue();
}

void WaveFunction::setPhi(double phi) {
  m_Angular.setPhi(phi);
  updateValue();
}

unsigned WaveFunction::getN() const {
  return m_Radial.getN();
}

unsigned WaveFunction::getL() const {
  return m_Radial.getL();
}

int WaveFunction::getM() const {
  return m_Angular.getOrder();
}

double WaveFunction::getR() const {
  return m_Radial.getR();
}

double WaveFunction::getTheta() const {
  return m_Angular.getTheta();
}

double WaveFunction::getPhi() const {
  return m_Angular.getPhi();
}

void WaveFunction::updateValue() {
  m_Value = m_Radial() * m_Angular();
}

}  // namespace math

}  // namespace orbitals
