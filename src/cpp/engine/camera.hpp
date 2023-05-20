#pragma once

#include "../math/matrix.hpp"

namespace orbitals {

namespace engine {

class Camera {
 private:
  math::vec3 m_Position;
  math::vec3 m_Center;
  math::vec3 m_UpVector;
  math::mat4 m_ViewMatrix;
  float m_FOV;
  float m_ZNear;
  float m_ZFar;

 public:
  Camera();
  Camera(float x, float y, float z);
  Camera(math::vec3 const& position);
  Camera& lookAt(float x, float y, float z);
  Camera& lookAt(math::vec3 const& center);
  Camera& translate(float x, float y, float z);
  Camera& translate(math::vec3 const& amount);
  Camera& translateX(float x);
  Camera& translateY(float y);
  Camera& translateZ(float z);
  Camera& setPosition(float x, float y, float z);
  Camera& setPosition(math::vec3 const& position);
  Camera& setX(float x);
  Camera& setY(float y);
  Camera& setZ(float z);
  Camera& setUpVector(math::vec3 const& upVector);
  Camera& setFOV(float fov);
  Camera& setZNear(float zNear);
  Camera& setZFar(float zFar);
  math::vec3 const& getPosition() const;
  float getX() const;
  float getY() const;
  float getZ() const;
  float getFOV() const;
  float getZNear() const;
  float getZFar() const;
  math::mat4 const& viewMatrix() const;

 private:
  void updateViewMatrix();
};

}  // namespace engine

}  // namespace orbitals