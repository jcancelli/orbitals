#pragma once

#include <complex>

namespace orbitals {

namespace math {

class SphericalHarmonics {
 private:
  std::complex<float> m_Value;
  int m_Order;
  int m_Degree;
  float m_Theta;
  float m_Phi;
  float m_normFactor;
  float m_ThetaFuncValue;
  std::complex<float> m_PhiFuncValue;

 public:
  SphericalHarmonics(int order = 0, int degree = 0);
  std::complex<float> operator()() const;
  std::complex<float> operator()(float theta, float phi);
  void setOrder(int order);
  void setDegree(int degree);
  void setTheta(float theta);
  void setPhi(float phi);
  int getOrder() const;
  int getDegree() const;
  float getTheta() const;
  float getPhi() const;

 private:
  void updateValue();
  void updateNormFactor();
  void updateThetaFuncValue();
  void updatePhiFuncValue();
};

}  // namespace math

}  // namespace orbitals
