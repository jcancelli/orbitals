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
generic_mat4<T>::generic_mat4(std::array<std::array<T, 4>, 4> values)
    : generic_square_mat<4, T>::generic_square_mat(values) {
}

template <class T>
generic_mat4<T>::generic_mat4(mat<4, 4, T> const& other)
    : generic_square_mat<4, T>::generic_square_mat(other) {
}

template <class T>
generic_mat4<T>::generic_mat4(quat<T> const& quaternion) {
  generic_mat4<T>& m = *this;

  const T qxx(quaternion.x * quaternion.x);
  const T qyy(quaternion.y * quaternion.y);
  const T qzz(quaternion.z * quaternion.z);
  const T qxz(quaternion.x * quaternion.z);
  const T qxy(quaternion.x * quaternion.y);
  const T qyz(quaternion.y * quaternion.z);
  const T qwx(quaternion.w * quaternion.x);
  const T qwy(quaternion.w * quaternion.y);
  const T qwz(quaternion.w * quaternion.z);

  m[0][0] = static_cast<T>(1) - static_cast<T>(2) * (qyy + qzz);
  m[0][1] = static_cast<T>(2) * (qxy + qwz);
  m[0][2] = static_cast<T>(2) * (qxz - qwy);
  m[0][3] = static_cast<T>(0);

  m[1][0] = static_cast<T>(2) * (qxy - qwz);
  m[1][1] = static_cast<T>(1) - static_cast<T>(2) * (qxx + qzz);
  m[1][2] = static_cast<T>(2) * (qyz + qwx);
  m[1][3] = static_cast<T>(0);

  m[2][0] = static_cast<T>(2) * (qxz + qwy);
  m[2][1] = static_cast<T>(2) * (qyz - qwx);
  m[2][2] = static_cast<T>(1) - static_cast<T>(2) * (qxx + qyy);
  m[2][3] = static_cast<T>(0);

  m[3][0] = static_cast<T>(0);
  m[3][1] = static_cast<T>(0);
  m[3][2] = static_cast<T>(0);
  m[3][3] = static_cast<T>(1);
}

template <class T>
generic_mat4<T>& generic_mat4<T>::translate(float x, float y, float z) {
  generic_mat4<T>& m = *this;
  m[3] += m[0] * x + m[1] * y + m[2] * z;
  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::translate(generic_vec3<T> const& amount) {
  return translate(amount[0], amount[1], amount[2]);
}

template <class T>
generic_mat4<T> generic_mat4<T>::translated(float x, float y, float z) const {
  return generic_mat4<T>(*this).translate(x, y, z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::translated(generic_vec3<T> const& amount) const {
  return generic_mat4<T>(*this).translate(amount);
}

template <class T>
generic_mat4<T>& generic_mat4<T>::rotate(T angle, generic_vec3<T> const& rotationAxis) {
  const T c = std::cos(angle);
  const T s = std::sin(angle);

  const generic_vec3<T> axis(rotationAxis.normalized());
  const generic_vec3<T> temp((T(1) - c) * axis);
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

  generic_mat4<T> m(*this);

  m[0] = m[0] * rotation[0][0] + m[1] * rotation[0][1] + m[2] * rotation[0][2];
  m[1] = m[0] * rotation[1][0] + m[1] * rotation[1][1] + m[2] * rotation[1][2];
  m[2] = m[0] * rotation[2][0] + m[1] * rotation[2][1] + m[2] * rotation[2][2];

  *this = m * *this;

  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::rotate(quat<T> const& quaternion) {
  *this = generic_mat4<T>(quaternion) * *this;
  return *this;
}

template <class T>
generic_mat4<T> generic_mat4<T>::rotated(T angle, generic_vec3<T> const& rotationAxis) const {
  return generic_mat4<T>(*this).rotate(angle, rotationAxis);
}

template <class T>
generic_mat4<T> generic_mat4<T>::rotated(quat<T> const& quaternion) const {
  return generic_mat4<T>(*this).rotate(quaternion);
}

template <class T>
generic_mat4<T>& generic_mat4<T>::scale(float x, float y, float z) {
  generic_mat4<T>& m = *this;
  m[0] *= x;
  m[1] *= y;
  m[2] *= z;
  return *this;
}

template <class T>
generic_mat4<T>& generic_mat4<T>::scale(generic_vec3<T> const& amount) {
  return scale(amount[0], amount[1], amount[2]);
}

template <class T>
generic_mat4<T> generic_mat4<T>::scaled(float x, float y, float z) const {
  return generic_mat4<T>(*this).scale(x, y, z);
}

template <class T>
generic_mat4<T> generic_mat4<T>::scaled(generic_vec3<T> const& amount) const {
  return generic_mat4<T>(*this).scale(amount);
}

template <class T>
mat<4, 4, T>& generic_mat4<T>::operator=(mat<4, 4, T> const& other) {
  return generic_square_mat<4, T>::operator=(other);
}

}  // namespace math

}  // namespace orbitals