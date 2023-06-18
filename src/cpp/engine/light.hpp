#pragma once

#include "../math/matrix.hpp"
#include "../math/vector.hpp"

namespace orbitals {

namespace engine {

class DirectionalLight {
 private:
  math::vec3 m_Color;
  math::vec3 m_InvertedDirection;
  OrthograficCamera m_Camera;

 public:
  DirectionalLight();
  DirectionalLight(math::vec3 invertedDirection, math::vec3 color = math::vec3(1, 1, 1));
  math::vec3 getColor() const;
  void setColor(math::vec3 const& color);
  math::vec3 getInvertedDirection() const;
  void setInvertedDirection(math::vec3 const& invertedDirection);
  OrthograficCamera const& getCamera() const;
  void setEffectedVolume(float left, float right, float bottom, float top);
};

}  // namespace engine

}  // namespace orbitals
