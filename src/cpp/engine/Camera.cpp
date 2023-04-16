#include "Camera.hpp"

#include "../math/trigonometry.hpp"

namespace orbitals {

namespace engine {

Camera::Camera() : m_ViewMatrix(1) {
}

Camera::Camera(float x, float y, float z) : m_Position(x, y, z), m_ViewMatrix(1) {
  lookAt(0, 0, -1, math::vec3(0, 1, 0));  // init view matrix
}

Camera::Camera(math::vec3 const& position) : m_Position(position), m_ViewMatrix(1) {
  lookAt(0, 0, -1, math::vec3(0, 1, 0));  // init view matrix
}

Camera& Camera::lookAt(float x, float y, float z, math::vec3 const& up) {
  m_Center.x = x;
  m_Center.y = y;
  m_Center.z = z;

  math::vec3 const f(m_Center.normalized());
  math::vec3 const s(f.cross(up).normalized());
  math::vec3 const u(s.cross(f));

  math::mat4 result(1);
  result[0][0] = s.x;
  result[1][0] = s.y;
  result[2][0] = s.z;
  result[0][1] = u.x;
  result[1][1] = u.y;
  result[2][1] = u.z;
  result[0][2] = -f.x;
  result[1][2] = -f.y;
  result[2][2] = -f.z;
  result[3][0] = -s.dot(m_Center);
  result[3][1] = -u.dot(m_Center);
  result[3][2] = f.dot(m_Center);

  m_ViewMatrix = result;

  return *this;
}

Camera& Camera::lookAt(math::vec3 const& center, math::vec3 const& up) {
  return lookAt(center.x, center.y, center.z, up);
}

Camera& Camera::translate(float x, float y, float z) {
  m_Position.x += x;
  m_Position.y += y;
  m_Position.z += z;
  m_ViewMatrix.translate(x, y, z);
  return *this;
}

Camera& Camera::translate(math::vec3 const& amount) {
  return translate(amount.x, amount.y, amount.z);
}

Camera& Camera::translateX(float x) {
  return translate(x, 0, 0);
}

Camera& Camera::translateY(float y) {
  return translate(0, y, 0);
}

Camera& Camera::translateZ(float z) {
  return translate(0, 0, z);
}

Camera& Camera::setPosition(float x, float y, float z) {
  return translate(x - m_Position.x, y - m_Position.y, z - m_Position.z);
}

Camera& Camera::setPosition(math::vec3 const& position) {
  return setPosition(position.x, position.y, position.z);
}

Camera& Camera::setX(float x) {
  return setPosition(x, m_Position.y, m_Position.z);
}

Camera& Camera::setY(float y) {
  return setPosition(m_Position.x, y, m_Position.z);
}

Camera& Camera::setZ(float z) {
  return setPosition(m_Position.x, m_Position.y, z);
}

math::vec3 const& Camera::getPosition() const {
  return m_Position;
}

float Camera::getX() const {
  return m_Position.x;
}

float Camera::getY() const {
  return m_Position.y;
}

float Camera::getZ() const {
  return m_Position.z;
}

math::mat4 const& Camera::viewMatrix() const {
  return m_ViewMatrix;
}

}  // namespace engine

}  // namespace orbitals