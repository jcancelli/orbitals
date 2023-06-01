#pragma once

#include "matrix.hpp"

namespace orbitals {

namespace math {

template <std::size_t tSize, class T>
generic_square_mat<tSize, T>::generic_square_mat() : mat<tSize, tSize, T>::mat() {
}

template <std::size_t tSize, class T>
generic_square_mat<tSize, T>::generic_square_mat(T identityValue) {
  for (int i = 0; i < tSize; i++) {
    (*this)[i][i] = identityValue;
  }
}

template <std::size_t tSize, class T>
generic_square_mat<tSize, T>::generic_square_mat(std::array<std::array<T, tSize>, tSize> values)
    : mat<tSize, tSize, T>::mat(values) {
}

template <std::size_t tSize, class T>
generic_square_mat<tSize, T>::generic_square_mat(mat<tSize, tSize, T> const& other)
    : mat<tSize, tSize, T>::mat(other) {
}

template <std::size_t tSize, class T>
mat<tSize, tSize, T>& generic_square_mat<tSize, T>::operator=(mat<tSize, tSize, T> const& other) {
  return mat<tSize, tSize, T>::operator=(other);
}

}  // namespace math

}  // namespace orbitals