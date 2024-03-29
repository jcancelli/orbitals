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
      m_MaxR{std::numeric_limits<float>::max()},
      m_MaxSpeedR{20},
      m_SpeedR{0},
      m_MinTheta{0.000001},
      m_MaxTheta{M_PI - 0.000001},
      m_MaxSpeedTheta{static_cast<float>(math::radians(100.f))},
      m_SpeedTheta{0},
      m_LimitTheta{true},
      m_MinPhi{0},
      m_MaxPhi{2 * M_PI},
      m_MaxSpeedPhi{static_cast<float>(math::radians(130.f))},
      m_SpeedPhi{0},
      m_LimitPhi{true},
      m_Center(center) {
  m_SpehericalPos =
      math::vec3(m_MinR, (m_MaxTheta + m_MinTheta) / 2.f, (m_MaxPhi + m_MinPhi) / 2.f);
  synchCamera();
}

void OrbitingCameraMovement::update(double deltaTime) {
  const double deltaTimeSeconds = deltaTime / 1000.;
  float newR = m_SpehericalPos[0] + m_SpeedR * deltaTimeSeconds;
  float newTheta = m_SpehericalPos[1] + m_SpeedTheta * deltaTimeSeconds;
  float newPhi = m_SpehericalPos[2] + m_SpeedPhi * deltaTimeSeconds;
  if (m_LimitTheta) {
    newTheta = std::min(m_MaxTheta, std::max(m_MinTheta, newTheta));
  } else {
    while (newTheta > M_PI) {
      newTheta -= M_PI;
      newPhi += M_PI;
    }
    while (newTheta < 0) {
      newTheta += M_PI;
      newPhi += M_PI;
    }
  }
  if (m_LimitPhi) {
    newPhi = std::min(m_MaxPhi, std::max(m_MinPhi, newPhi));
  } else {
    while (newPhi > M_PI * 2) {
      newPhi -= M_PI * 2;
    }
    while (newPhi < 0) {
      newPhi += M_PI * 2;
    }
  }
  m_SpehericalPos = math::vec3(                  //
      std::min(m_MaxR, std::max(m_MinR, newR)),  //
      newTheta,                                  //
      newPhi                                     //
  );                                             //
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
  if (m_LimitTheta) {
    assert(position[1] >= m_MinTheta && position[1] <= m_MaxTheta);
  }
  if (m_LimitPhi) {
    assert(position[2] >= m_MinPhi && position[2] <= m_MaxPhi);
  }
  m_SpehericalPos = position;
  synchCamera();
}

void OrbitingCameraMovement::setPosition(float r, float theta, float phi) {
  setPosition(math::vec3(r, theta, phi));
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

void OrbitingCameraMovement::setMaxSpeedR(float speed) {
  assert(speed >= 0);
  m_MaxSpeedR = speed;
}

void OrbitingCameraMovement::setMaxSpeedTheta(float speed) {
  assert(speed >= 0);
  m_MaxSpeedTheta = speed;
}

void OrbitingCameraMovement::setMaxSpeedPhi(float speed) {
  assert(speed >= 0);
  m_MaxSpeedPhi = speed;
}

void OrbitingCameraMovement::setLimitTheta(bool limit) {
  m_LimitTheta = limit;
  if (limit) {
    m_SpehericalPos[1] = std::min(m_MaxTheta, std::max(m_MinTheta, m_SpehericalPos[1]));
  }
}

void OrbitingCameraMovement::setLimitPhi(bool limit) {
  m_LimitPhi = limit;
  if (limit) {
    m_SpehericalPos[2] = std::min(m_MaxPhi, std::max(m_MinPhi, m_SpehericalPos[2]));
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

float OrbitingCameraMovement::getMaxSpeedR() const {
  return m_MaxSpeedR;
}

float OrbitingCameraMovement::getMaxSpeedTheta() const {
  return m_MaxSpeedTheta;
}

float OrbitingCameraMovement::getMaxSpeedPhi() const {
  return m_MaxSpeedPhi;
}

bool OrbitingCameraMovement::getLimitTheta() const {
  return m_LimitTheta;
}

bool OrbitingCameraMovement::getLimitPhi() const {
  return m_LimitPhi;
}

void OrbitingCameraMovement::synchCamera() {
  m_Camera->setPosition(math::cartesian(m_SpehericalPos) + m_Center);
  m_Camera->lookAt(m_Center);
}

}  // namespace engine

}  // namespace orbitals