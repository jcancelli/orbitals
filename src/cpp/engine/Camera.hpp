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
  math::vec3 const& getPosition() const;
  float getX() const;
  float getY() const;
  float getZ() const;
  Camera& setUpVector(math::vec3 const& upVector);
  const math::mat4& viewMatrix() const;

 private:
  void updateViewMatrix();
};

}  // namespace engine

}  // namespace orbitals