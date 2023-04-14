#pragma once

#include <cmath>

#include "matrix.hpp"

namespace math {

template <typename T>
mat<4, 4, T> orthogonal(T left, T right, T bottom, T top, T zNear, T zFar) {
  mat<4, 4, T> result(1);
  result[0][0] = static_cast<T>(2) / (right - left);
  result[1][1] = static_cast<T>(2) / (top - bottom);
  result[2][2] = -static_cast<T>(2) / (zFar - zNear);
  result[3][0] = -(right + left) / (right - left);
  result[3][1] = -(top + bottom) / (top - bottom);
  result[3][2] = -(zFar + zNear) / (zFar - zNear);
  return result;
}

template <typename T>
mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar) {
  T const tanHalfFovy = std::tan(fovy / static_cast<T>(2));
  mat<4, 4, T> result;
  result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
  result[1][1] = static_cast<T>(1) / (tanHalfFovy);
  result[2][2] = -(zFar + zNear) / (zFar - zNear);
  result[2][3] = -static_cast<T>(1);
  result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
  return result;
}

template <typename T>
mat<4, 4, T> perspective(T fov, T width, T height, T zNear, T zFar) {
  assert(width > static_cast<T>(0));
  assert(height > static_cast<T>(0));
  assert(fov > static_cast<T>(0));

  T const rad = fov;
  T const h = std::cos(static_cast<T>(0.5) * rad) / std::sin(static_cast<T>(0.5) * rad);
  T const w = h * height / width;
  mat<4, 4, T> result;
  result[0][0] = w;
  result[1][1] = h;
  result[2][2] = -(zFar + zNear) / (zFar - zNear);
  result[2][3] = -static_cast<T>(1);
  result[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
  return result;
}

template <typename T>
mat<4, 4, T> infinitePerspective(T fovy, T aspect, T zNear) {
  T const range = std::tan(fovy / static_cast<T>(2)) * zNear;
  T const left = -range * aspect;
  T const right = range * aspect;
  T const bottom = -range;
  T const top = range;
  mat<4, 4, T> result;
  result[0][0] = (static_cast<T>(2) * zNear) / (right - left);
  result[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
  result[2][2] = -static_cast<T>(1);
  result[2][3] = -static_cast<T>(1);
  result[3][2] = -static_cast<T>(2) * zNear;
  return result;
}

};  // namespace math