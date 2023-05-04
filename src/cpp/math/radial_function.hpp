#pragma once

namespace orbitals {

namespace math {

class RadialFunction {
 private:
  unsigned m_N;
  unsigned m_L;
  double m_R;
  double m_normFactor;
  double m_Value;

 public:
  RadialFunction();
  RadialFunction(unsigned n, unsigned l);
  double operator()() const;
  double operator()(double r);
  void setN(unsigned n);
  void setL(unsigned l);
  void setR(double r);
  unsigned getN() const;
  unsigned getL() const;
  double getR() const;

 private:
  void updateValue();
  void updateNormFactor();
};

}  // namespace math

}  // namespace orbitals
