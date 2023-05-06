#pragma once

#include "radial_function.hpp"
#include "spherical_harmonics.hpp"

namespace orbitals {

namespace math {

class WaveFunction {
 private:
  RadialFunction m_Radial;
  SphericalHarmonics m_Angular;
  std::complex<double> m_Value;

 public:
  WaveFunction();
  WaveFunction(unsigned n, unsigned l, int m);
  std::complex<double> operator()() const;
  std::complex<double> operator()(double r, double theta, double phi);
  void setN(unsigned n);
  void setL(unsigned l);
  void setM(int m);
  void setR(double r);
  void setTheta(double theta);
  void setPhi(double phi);
  unsigned getN() const;
  unsigned getL() const;
  int getM() const;
  double getR() const;
  double getTheta() const;
  double getPhi() const;

 private:
  void updateValue();
};

}  // namespace math

}  // namespace orbitals
