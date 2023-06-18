#include "camera.hpp"

#include "../math/projection_matrix.hpp"
#include "../math/trigonometry.hpp"

namespace orbitals {

namespace engine {

static const float defaultZNear = 0.1f;
static const float defaultZFar = 2000.f;

Camera::Camera()
    : m_Position(0),
      m_Center(0),
      m_UpVector(0, 1, 0),
      m_ViewMatrix(1),
      m_ZNear{defaultZNear},
      m_ZFar{defaultZFar} {
  updateViewMatrix(false);
}

Camera::Camera(float x, float y, float z)
    : m_Position(x, y, z),
      m_Center(0),
      m_UpVector(0, 1, 0),
      m_ViewMatrix(1),
      m_ZNear{defaultZNear},
      m_ZFar{defaultZFar} {
  updateViewMatrix(false);
}

Camera::Camera(math::vec3 const& position)
    : m_Position(position),
      m_Center(0),
      m_UpVector(0, 1, 0),
      m_ViewMatrix(1),
      m_ZNear{defaultZNear},
      m_ZFar{defaultZFar} {
  updateViewMatrix(false);
}

void Camera::lookAt(float x, float y, float z) {
  m_Center(x, y, z);
  updateViewMatrix(true);
}

void Camera::lookAt(math::vec3 const& center) {
  m_Center = center;
  updateViewMatrix(true);
}

void Camera::translate(float x, float y, float z) {
  m_Position.x() += x;
  m_Position.y() += y;
  m_Position.z() += z;
  updateViewMatrix(true);
}

void Camera::translate(math::vec3 const& amount) {
  return translate(amount.x(), amount.y(), amount.z());
}

void Camera::translateX(float x) {
  return translate(x, 0, 0);
}

void Camera::translateY(float y) {
  return translate(0, y, 0);
}

void Camera::translateZ(float z) {
  return translate(0, 0, z);
}

void Camera::setPosition(float x, float y, float z) {
  m_Position(x, y, z);
  updateViewMatrix(true);
}

void Camera::setPosition(math::vec3 const& position) {
  return setPosition(position.x(), position.y(), position.z());
}

void Camera::setX(float x) {
  return setPosition(x, m_Position.y(), m_Position.z());
}

void Camera::setY(float y) {
  return setPosition(m_Position.x(), y, m_Position.z());
}

void Camera::setZ(float z) {
  return setPosition(m_Position.x(), m_Position.y(), z);
}

void Camera::setUpVector(math::vec3 const& upVector) {
  m_UpVector = upVector;
  updateViewMatrix(true);
}

void Camera::setZNear(float zNear) {
  assert(zNear > 0 && zNear < m_ZFar);
  m_ZNear = zNear;
  updateProjectionMatrix(true);
}

void Camera::setZFar(float zFar) {
  assert(zFar > m_ZNear);
  m_ZFar = zFar;
  updateProjectionMatrix(true);
}

math::vec3 Camera::getPosition() const {
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

float Camera::getZNear() const {
  return m_ZNear;
}

float Camera::getZFar() const {
  return m_ZFar;
}

math::mat4 Camera::getCameraMatrix() const {
  return m_CameraMatrix;
}

math::mat4 Camera::getViewMatrix() const {
  return m_ViewMatrix;
}

math::mat4 Camera::getProjectionMatrix() const {
  return m_ProjectionMatrix;
}

void Camera::updateCameraMatrix() {
  m_CameraMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void Camera::updateViewMatrix(bool updateCameraMatrix) {
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

  if (updateCameraMatrix) {
    this->updateCameraMatrix();
  }
}

OrthograficCamera::OrthograficCamera() : m_Left{-1}, m_Right{1}, m_Bottom{-1}, m_Top{1} {
  updateProjectionMatrix(true);
}

OrthograficCamera::OrthograficCamera(float x, float y, float z, float left, float right,
                                     float bottom, float top)
    : Camera::Camera(x, y, z), m_Left{left}, m_Right{right}, m_Bottom{bottom}, m_Top{top} {
  updateProjectionMatrix(true);
}

OrthograficCamera::OrthograficCamera(math::vec3 const& position, float left, float right,
                                     float bottom, float top)
    : Camera::Camera(position), m_Left{left}, m_Right{right}, m_Bottom{bottom}, m_Top{top} {
  updateProjectionMatrix(true);
}

void OrthograficCamera::setLeft(float left) {
  m_Left = left;
  updateProjectionMatrix(true);
}

void OrthograficCamera::setRight(float right) {
  m_Right = right;
  updateProjectionMatrix(true);
}

void OrthograficCamera::setBottom(float bottom) {
  m_Bottom = bottom;
  updateProjectionMatrix(true);
}

void OrthograficCamera::setTop(float top) {
  m_Top = top;
  updateProjectionMatrix(true);
}

float OrthograficCamera::getLeft() const {
  return m_Left;
}

float OrthograficCamera::getRight() const {
  return m_Right;
}

float OrthograficCamera::getBottom() const {
  return m_Bottom;
}

float OrthograficCamera::getTop() const {
  return m_Top;
}

void OrthograficCamera::updateProjectionMatrix(bool updateCameraMatrix) {
  m_ProjectionMatrix = math::orthografic<float>(m_Left, m_Right, m_Bottom, m_Top, m_ZNear, m_ZFar);
  if (updateCameraMatrix) {
    this->updateCameraMatrix();
  }
}

static const float defaultFOV = math::radians(45);
static const float defaultAspectRatio = 1;

PerspectiveCamera::PerspectiveCamera() : m_FOV{defaultFOV}, m_AspectRatio{defaultAspectRatio} {
  updateProjectionMatrix(true);
}

PerspectiveCamera::PerspectiveCamera(float x, float y, float z, float fov, float aspectRatio)
    : Camera::Camera(x, y, z), m_FOV{fov}, m_AspectRatio{aspectRatio} {
  updateProjectionMatrix(true);
}

PerspectiveCamera::PerspectiveCamera(math::vec3 const& position, float fov, float aspectRatio)
    : Camera::Camera(position), m_FOV{fov}, m_AspectRatio{aspectRatio} {
  updateProjectionMatrix(true);
}

void PerspectiveCamera::setFOV(float fov) {
  assert(fov > 0);
  m_FOV = fov;
  updateProjectionMatrix(true);
}

void PerspectiveCamera::setAspectRatio(float aspectRatio) {
  assert(aspectRatio > 0);
  m_AspectRatio = aspectRatio;
  updateProjectionMatrix(true);
}

float PerspectiveCamera::getFOV() const {
  return m_FOV;
}

float PerspectiveCamera::getAspectRatio() const {
  return m_AspectRatio;
}

void PerspectiveCamera::updateProjectionMatrix(bool updateCameraMatrix) {
  m_ProjectionMatrix = math::perspective<float>(m_FOV, m_AspectRatio, m_ZNear, m_ZFar);
  if (updateCameraMatrix) {
    this->updateCameraMatrix();
  }
}

}  // namespace engine

}  // namespace orbitals