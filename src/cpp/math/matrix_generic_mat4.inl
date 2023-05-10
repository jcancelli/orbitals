#pragma once

#include "matrix.hpp"

namespace orbitals {

namespace math {

template <class T>
generic_mat4<T>::generic_mat4() : generic_square_mat<4, T>::generic_square_mat() {
}

template <class T>
generic_mat4<T>::generic_mat4(T identityValue)
    : generic_square_mat<4, T>::generic_square_mat(identityValue) {
}

template <class T>
generic_mat4<T>::generic_mat4(mat<4, 4, T> const& other)
    : generic_square_mat<4, T>::generic_square_mat(other) {
}

template <class T>
generic_mat4<T>& generic_mat4<T>::translate(float x, float y, float z) {
  generic_mat4<T>& m = *this;
  m[3] = m[0] * x + m[1] * y + m[2] * z + m[3];
  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::translate(vec<3, T> const& amount) {
  return translate(amount[0], amount[1], amount[2]);
}

template <class T>
generic_mat4<T> generic_mat4<T>::translated(float x, float y, float z) const {
  return generic_mat4<T>(*this).translate(x, y, z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::translated(vec<3, T> const& amount) const {
  return generic_mat4<T>(*this).translate(amount);
}

template <class T>
generic_mat4<T>& generic_mat4<T>::rotate(T angle, generic_vec3<T> const& rotationAxis) {
  T const c = std::cos(angle);
  T const s = std::sin(angle);

  generic_vec3<T> axis(rotationAxis.normalized());
  generic_vec3<T> temp((T(1) - c) * axis);
  generic_mat4<T> rotation;

  rotation[0][0] = c + temp[0] * axis[0];
  rotation[0][1] = temp[0] * axis[1] + s * axis[2];
  rotation[0][2] = temp[0] * axis[2] - s * axis[1];

  rotation[1][0] = temp[1] * axis[0] - s * axis[2];
  rotation[1][1] = c + temp[1] * axis[1];
  rotation[1][2] = temp[1] * axis[2] + s * axis[0];

  rotation[2][0] = temp[2] * axis[0] + s * axis[1];
  rotation[2][1] = temp[2] * axis[1] - s * axis[0];
  rotation[2][2] = c + temp[2] * axis[2];

  generic_mat4<T>& m(*this);
  generic_mat4<T>& result = *this;

  result[0] = m[0] * rotation[0][0] + m[1] * rotation[0][1] + m[2] * rotation[0][2];
  result[1] = m[0] * rotation[1][0] + m[1] * rotation[1][1] + m[2] * rotation[1][2];
  result[2] = m[0] * rotation[2][0] + m[1] * rotation[2][1] + m[2] * rotation[2][2];
  result[3] = m[3];

  return *this;
}

template <class T>
generic_mat4<T> generic_mat4<T>::rotated(T angle, vec<3, T> const& rotationAxis) const {
  return generic_mat4<T>(*this).rotate(angle, rotationAxis);
}

template <class T>
generic_mat4<T>& generic_mat4<T>::scale(float x, float y, float z) {
  generic_mat4<T> m(*this);
  generic_mat4<T>& result = *this;

  result[0] = m[0] * x;
  result[1] = m[1] * y;
  result[2] = m[2] * z;
  result[3] = m[3];

  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::scale(vec<3, T> const& amount) {
  return scale(amount[0], amount[1], amount[2]);
}

template <class T>
generic_mat4<T> generic_mat4<T>::scaled(float x, float y, float z) const {
  return generic_mat4<T>(*this).scale(x, y, z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::scaled(vec<3, T> const& amount) const {
  return generic_mat4<T>(*this).scale(amount);
}

template <class T>
mat<4, 4, T>& generic_mat4<T>::operator=(mat<4, 4, T> const& other) {
  return generic_square_mat<4, T>::operator=(other);
}

}  // namespace math

}  // namespace orbitals