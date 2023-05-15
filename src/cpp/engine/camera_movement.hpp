#pragma once

#include <memory>

#include "../math/vector.hpp"
#include "camera.hpp"

namespace orbitals {

namespace engine {

class CameraMovement {
 protected:
  std::shared_ptr<Camera> m_Camera;

 public:
  CameraMovement(std::shared_ptr<Camera> camera);
  virtual void update(double deltaTime) = 0;
  virtual void moveUp() = 0;
  virtual void moveDown() = 0;
  virtual void moveForward() = 0;
  virtual void moveBack() = 0;
  virtual void moveLeft() = 0;
  virtual void moveRight() = 0;
  virtual void rotateX() = 0;
  virtual void rotateY() = 0;
  virtual void rotateZ() = 0;
};

class OrbitingCameraMovement : public CameraMovement {
 protected:
  float m_MinR, m_MaxR, m_MaxSpeedR, m_SpeedR;  // units-of-length and units-of-length/second
  float m_MinTheta, m_MaxTheta, m_MaxSpeedTheta, m_SpeedTheta;  // radians and radians/second
  float m_MinPhi, m_MaxPhi, m_MaxSpeedPhi, m_SpeedPhi;          // radians and radians/second
  math::vec3 m_Center;         // x, y, z - The point the camera is orbiting
  math::vec3 m_SpehericalPos;  // r, theta, phi - The position of the camera in spherical coords

 public:
  OrbitingCameraMovement(std::shared_ptr<Camera> camera, math::vec3 const& center);
  void update(double deltaTime);
  void moveUp();
  void moveDown();
  void moveForward();
  void moveBack();
  void moveLeft();
  void moveRight();
  void rotateX();
  void rotateY();
  void rotateZ();
  void setPosition(math::vec3 const& position);       // Position in spherical coordinates
  void setPosition(float r, float theta, float phi);  // Position in spherical coordinates
  math::vec3 const& getPosition() const;              // Position in spherical coordinates
  void setCenter(math::vec3 const& center);
  math::vec3 const& getCenter() const;
  void setMinR(float value);
  void setMinTheta(float value);
  void setMinPhi(float value);
  void setMaxR(float value);
  void setMaxTheta(float value);
  void setMaxPhi(float value);
  float getMinR() const;
  float getMinTheta() const;
  float getMinPhi() const;
  float getMaxR() const;
  float getMaxTheta() const;
  float getMaxPhi() const;

 protected:
  void synchCamera();
};

}  // namespace engine

}  // namespace orbitals