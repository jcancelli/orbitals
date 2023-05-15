#include "camera_movement.hpp"

#include <algorithm>
#include <cassert>
#include <limits>

#include "../math/coordinates.hpp"
#include "../math/trigonometry.hpp"

namespace orbitals {

namespace engine {

CameraMovement::CameraMovement(std::shared_ptr<Camera> camera) : m_Camera(camera) {
}

OrbitingCameraMovement::OrbitingCameraMovement(std::shared_ptr<Camera> camera,
                                               math::vec3 const& center)
    : CameraMovement::CameraMovement(camera),
      m_MinR{1},
      m_MinTheta{0.000001},
      m_MinPhi{0},
      m_MaxR{std::numeric_limits<float>::max()},
      m_MaxTheta{M_PI - 0.000001},
      m_MaxPhi{2 * M_PI},
      m_MaxSpeedR{20},
      m_MaxSpeedTheta{static_cast<float>(math::radians(70.f))},
      m_MaxSpeedPhi{static_cast<float>(math::radians(70.f))},
      m_SpeedR{0},
      m_SpeedTheta{0},
      m_SpeedPhi{0},
      m_Center(center) {
  m_SpehericalPos =
      math::vec3(m_MinR, (m_MaxTheta + m_MinTheta) / 2.f, (m_MaxPhi + m_MinPhi) / 2.f);
  synchCamera();
}

void OrbitingCameraMovement::update(double deltaTime) {
  const double deltaTimeSeconds = deltaTime / 1000.;
  const float newR = m_SpehericalPos[0] + m_SpeedR * deltaTimeSeconds;
  const float newTheta = m_SpehericalPos[1] + m_SpeedTheta * deltaTimeSeconds;
  const float newPhi = m_SpehericalPos[2] + m_SpeedPhi * deltaTimeSeconds;
  m_SpehericalPos = math::vec3(                              //
      std::min(m_MaxR, std::max(m_MinR, newR)),              //
      std::min(m_MaxTheta, std::max(m_MinTheta, newTheta)),  //
      std::min(m_MaxPhi, std::max(m_MinPhi, newPhi))         //
  );                                                         //
  synchCamera();
  m_SpeedR = 0;
  m_SpeedTheta = 0;
  m_SpeedPhi = 0;
}

void OrbitingCameraMovement::moveUp() {
  m_SpeedTheta = std::max(-m_MaxSpeedTheta, m_SpeedTheta - m_MaxSpeedTheta);
}

void OrbitingCameraMovement::moveDown() {
  m_SpeedTheta = std::min(m_MaxSpeedTheta, m_SpeedTheta + m_MaxSpeedTheta);
}

void OrbitingCameraMovement::moveForward() {
  m_SpeedR = std::max(-m_MaxSpeedR, m_SpeedR - m_MaxSpeedR);
}

void OrbitingCameraMovement::moveBack() {
  m_SpeedR = std::min(m_MaxSpeedR, m_SpeedR + m_MaxSpeedR);
}

void OrbitingCameraMovement::moveLeft() {
  m_SpeedPhi = std::max(-m_MaxSpeedPhi, m_SpeedPhi - m_MaxSpeedPhi);
}

void OrbitingCameraMovement::moveRight() {
  m_SpeedPhi = std::min(m_MaxSpeedPhi, m_SpeedPhi + m_MaxSpeedPhi);
}

void OrbitingCameraMovement::rotateX() {
  // do nothing
}

void OrbitingCameraMovement::rotateY() {
  // do nothing
}

void OrbitingCameraMovement::rotateZ() {
  // do nothing
}

void OrbitingCameraMovement::setPosition(math::vec3 const& position) {
  assert(position[0] >= m_MinR && position[0] <= m_MaxR);
  assert(position[1] >= m_MinTheta && position[1] <= m_MaxTheta);
  assert(position[2] >= m_MinPhi && position[2] <= m_MaxPhi);
  m_SpehericalPos = position;
  synchCamera();
}

math::vec3 const& OrbitingCameraMovement::getPosition() const {
  return m_SpehericalPos;
}

void OrbitingCameraMovement::setCenter(math::vec3 const& center) {
  m_Center = center;
  synchCamera();
}

math::vec3 const& OrbitingCameraMovement::getCenter() const {
  return m_Center;
}

void OrbitingCameraMovement::setMinR(float value) {
  assert(value > 0);
  assert(value < m_MaxR);
  m_MinR = value;
  if (m_SpehericalPos[0] < m_MinR) {
    setPosition(math::vec3(m_MinR, m_SpehericalPos[1], m_SpehericalPos[2]));
  }
}

void OrbitingCameraMovement::setMinTheta(float value) {
  assert(value > 0);
  assert(value < m_MaxTheta);
  assert(value < M_PI);
  m_MinTheta = value;
  if (m_SpehericalPos[1] < m_MinTheta) {
    setPosition(math::vec3(m_SpehericalPos[0], m_MinTheta, m_SpehericalPos[2]));
  }
}

void OrbitingCameraMovement::setMinPhi(float value) {
  assert(value > 0);
  assert(value < m_MaxPhi);
  assert(value < 2 * M_PI);
  m_MinPhi = value;
  if (m_SpehericalPos[2] < m_MinPhi) {
    setPosition(math::vec3(m_SpehericalPos[0], m_SpehericalPos[2], m_MinPhi));
  }
}

void OrbitingCameraMovement::setMaxR(float value) {
  assert(value > 0);
  assert(value > m_MinR);
  m_MaxR = value;
  if (m_SpehericalPos[0] > m_MaxR) {
    setPosition(math::vec3(m_MaxR, m_SpehericalPos[1], m_SpehericalPos[2]));
  }
}

void OrbitingCameraMovement::setMaxTheta(float value) {
  assert(value > 0);
  assert(value > m_MinTheta);
  assert(value < M_PI);
  m_MaxTheta = value;
  if (m_SpehericalPos[1] > m_MaxTheta) {
    setPosition(math::vec3(m_SpehericalPos[0], m_MaxTheta, m_SpehericalPos[2]));
  }
}

void OrbitingCameraMovement::setMaxPhi(float value) {
  assert(value > 0);
  assert(value > m_MinPhi);
  assert(value < 2 * M_PI);
  m_MaxPhi = value;
  if (m_SpehericalPos[2] > m_MaxPhi) {
    setPosition(math::vec3(m_SpehericalPos[0], m_SpehericalPos[2], m_MaxPhi));
  }
}

float OrbitingCameraMovement::getMinR() const {
  return m_MinR;
}

float OrbitingCameraMovement::getMinTheta() const {
  return m_MinTheta;
}

float OrbitingCameraMovement::getMinPhi() const {
  return m_MinPhi;
}

float OrbitingCameraMovement::getMaxR() const {
  return m_MaxR;
}

float OrbitingCameraMovement::getMaxTheta() const {
  return m_MaxTheta;
}

float OrbitingCameraMovement::getMaxPhi() const {
  return m_MaxPhi;
}

void OrbitingCameraMovement::synchCamera() {
  m_Camera->setPosition(math::cartesian(m_SpehericalPos) + m_Center).lookAt(m_Center);
}

}  // namespace engine

}  // namespace orbitals