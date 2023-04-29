#pragma once

#include <cmath>
#include <type_traits>

namespace orbitals {

namespace math {

float inversesqrt(float value);
int factorial(int n);

// copy paste from c++ 23 standard library
template <typename T>
inline T legendre(unsigned int l, T x) {
  if (isnan(x))
    return std::numeric_limits<T>::quiet_NaN();
  else if (x == +T(1))
    return +T(1);
  else if (x == -T(1))
    return (l % 2 == 1 ? -T(1) : +T(1));
  else {
    T __p_lm2 = T(1);
    if (l == 0) return __p_lm2;

    T __p_lm1 = x;
    if (l == 1) return __p_lm1;

    T __p_l = 0;
    for (unsigned int __ll = 2; __ll <= l; ++__ll) {
      //  This arrangement is supposed to be better for roundoff
      //  protection, Arfken, 2nd Ed, Eq 12.17a.
      __p_l = T(2) * x * __p_lm1 - __p_lm2 - (x * __p_lm1 - __p_lm2) / T(__ll);
      __p_lm2 = __p_lm1;
      __p_lm1 = __p_l;
    }

    return __p_l;
  }
}

// copy paste from c++ 23 standard library
template <typename T>
inline T assocLegendre(unsigned int l, unsigned int m, T x, T phase = T(+1)) {
  if (m > l)
    return T(0);
  else if (isnan(x))
    return std::numeric_limits<T>::quiet_NaN();
  else if (m == 0)
    return legendre(l, x);
  else {
    T __p_mm = T(1);
    if (m > 0) {
      //  Two square roots seem more accurate more of the time
      //  than just one.
      T __root = std::sqrt(T(1) - x) * std::sqrt(T(1) + x);
      T __fact = T(1);
      for (unsigned int __i = 1; __i <= m; ++__i) {
        __p_mm *= phase * __fact * __root;
        __fact += T(2);
      }
    }
    if (l == m) return __p_mm;

    T __p_mp1m = T(2 * m + 1) * x * __p_mm;
    if (l == m + 1) return __p_mp1m;

    T __p_lm2m = __p_mm;
    T __P_lm1m = __p_mp1m;
    T __p_lm = T(0);
    for (unsigned int __j = m + 2; __j <= l; ++__j) {
      __p_lm = (T(2 * __j - 1) * x * __P_lm1m - T(__j + m - 1) * __p_lm2m) / T(__j - m);
      __p_lm2m = __P_lm1m;
      __P_lm1m = __p_lm;
    }

    return __p_lm;
  }
}

}  // namespace math

}  // namespace orbitals