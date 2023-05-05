#pragma once

#include <complex>

namespace orbitals {

namespace math {

class SphericalHarmonics {
 private:
  std::complex<double> m_Value;
  int m_Order;
  int m_Degree;
  double m_Theta;
  double m_Phi;
  double m_normFactor;
  double m_ThetaFuncValue;
  std::complex<double> m_PhiFuncValue;

 public:
  SphericalHarmonics(int order = 0, int degree = 0);
  std::complex<double> operator()() const;
  std::complex<double> operator()(double theta, double phi);
  void setOrder(int order);
  void setDegree(int degree);
  void setTheta(double theta);
  void setPhi(double phi);
  int getOrder() const;
  int getDegree() const;
  double getTheta() const;
  double getPhi() const;

 private:
  void updateValue();
  void updateNormFactor();
  void updateThetaFuncValue();
  void updatePhiFuncValue();
};

}  // namespace math

}  // namespace orbitals
