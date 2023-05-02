#pragma once

namespace orbitals {

namespace math {

class RadialFunction {
 private:
  unsigned m_N;
  unsigned m_L;
  float m_normFactor;

 public:
  RadialFunction(unsigned n, unsigned l);
  float operator()(float r) const;
  void setN(unsigned n);
  void setL(unsigned l);
  unsigned getN() const;
  unsigned getL() const;

 private:
  void updateNormFactor();
};

}  // namespace math

}  // namespace orbitals
