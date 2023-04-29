#pragma once

#include <complex>

namespace orbitals {

namespace math {

class SphericalHarmonics {
 private:
  int m_Order;
  int m_Degree;
  float m_normFactor;

 public:
  SphericalHarmonics(int order = 0, int degree = 0);
  std::complex<float> operator()(float theta, float phi) const;
  void setOrder(int order);
  void setDegree(int degree);
  int getOrder() const;
  int getDegree() const;

 private:
  void updateNormFactor();
};

}  // namespace math

}  // namespace orbitals
