#pragma once

namespace orbitals {

namespace math {

class RadialFunction {
 private:
  unsigned m_N;
  unsigned m_L;
  float m_R;
  float m_normFactor;
  float m_Value;

 public:
  RadialFunction();
  RadialFunction(unsigned n, unsigned l);
  float operator()() const;
  float operator()(float r);
  void setN(unsigned n);
  void setL(unsigned l);
  void setR(float r);
  unsigned getN() const;
  unsigned getL() const;
  float getR() const;

 private:
  void updateValue();
  void updateNormFactor();
};

}  // namespace math

}  // namespace orbitals
