#include "camera.hpp"

#include "../math/trigonometry.hpp"

namespace orbitals {

namespace engine {

static const float defaultFOV = math::radians(45);
static const float defaultZNear = 0.1f;
static const float defaultZFar = 2000.f;

Camera::Camera()
    : m_Position(0),
      m_Center(0),
      m_UpVector(0, 1, 0),
      m_ViewMatrix(1),
      m_FOV{defaultFOV},
      m_ZNear{defaultZNear},
      m_ZFar{defaultZFar} {
}

Camera::Camera(float x, float y, float z)
    : m_Position(x, y, z),
      m_Center(0),
      m_UpVector(0, 1, 0),
      m_ViewMatrix(1),
      m_FOV{defaultFOV},
      m_ZNear{defaultZNear},
      m_ZFar{defaultZFar} {
  updateViewMatrix();
}

Camera::Camera(math::vec3 const& position)
    : m_Position(position),
      m_Center(0),
      m_UpVector(0, 1, 0),
      m_ViewMatrix(1),
      m_FOV{defaultFOV},
      m_ZNear{defaultZNear},
      m_ZFar{defaultZFar} {
  updateViewMatrix();
}

Camera& Camera::lookAt(float x, float y, float z) {
  m_Center(x, y, z);
  updateViewMatrix();
  return *this;
}

Camera& Camera::lookAt(math::vec3 const& center) {
  m_Center = center;
  updateViewMatrix();
  return *this;
}

Camera& Camera::translate(float x, float y, float z) {
  m_Position.x() += x;
  m_Position.y() += y;
  m_Position.z() += z;
  updateViewMatrix();
  return *this;
}

Camera& Camera::translate(math::vec3 const& amount) {
  return translate(amount.x(), amount.y(), amount.z());
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
  m_Position(x, y, z);
  updateViewMatrix();
  return *this;
}

Camera& Camera::setPosition(math::vec3 const& position) {
  return setPosition(position.x(), position.y(), position.z());
}

Camera& Camera::setX(float x) {
  return setPosition(x, m_Position.y(), m_Position.z());
}

Camera& Camera::setY(float y) {
  return setPosition(m_Position.x(), y, m_Position.z());
}

Camera& Camera::setZ(float z) {
  return setPosition(m_Position.x(), m_Position.y(), z);
}

Camera& Camera::setUpVector(math::vec3 const& upVector) {
  m_UpVector = upVector;
  updateViewMatrix();
  return *this;
}

Camera& Camera::setFOV(float fov) {
  assert(fov > 0);
  m_FOV = fov;
  return *this;
}

Camera& Camera::setZNear(float zNear) {
  assert(zNear > 0 && zNear < m_ZFar);
  m_ZNear = zNear;
  return *this;
}

Camera& Camera::setZFar(float zFar) {
  assert(zFar > m_ZNear);
  m_ZFar = zFar;
  return *this;
}

math::vec3 const& Camera::getPosition() const {
  return m_Position;
}

float Camera::getX() const {
  return m_Position.x();
}

float Camera::getY() const {
  return m_Position.y();
}

float Camera::getZ() const {
  return m_Position.z();
}

float Camera::getFOV() const {
  return m_FOV;
}

float Camera::getZNear() const {
  return m_ZNear;
}

float Camera::getZFar() const {
  return m_ZFar;
}

math::mat4 const& Camera::viewMatrix() const {
  return m_ViewMatrix;
}

void Camera::updateViewMatrix() {
  math::vec3 const f((m_Center - m_Position).normalized());
  math::vec3 const s(f.cross(m_UpVector).normalized());
  math::vec3 const u(s.cross(f));

  math::mat4 result(1);
  result[0][0] = s.x();
  result[1][0] = s.y();
  result[2][0] = s.z();
  result[0][1] = u.x();
  result[1][1] = u.y();
  result[2][1] = u.z();
  result[0][2] = -f.x();
  result[1][2] = -f.y();
  result[2][2] = -f.z();
  result[3][0] = -s.dot(m_Position);
  result[3][1] = -u.dot(m_Position);
  result[3][2] = f.dot(m_Position);

  m_ViewMatrix = result;
}

}  // namespace engine

}  // namespace orbitals