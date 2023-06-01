#pragma once

#include "../math/matrix.hpp"
#include "../math/vector.hpp"

namespace orbitals {

namespace engine {

class Light {
 private:
  math::vec3 m_Color;

 public:
  Light();
  Light(math::vec3 color);
  math::vec3 getColor() const;
  void setColor(math::vec3 const& color);
};

class DirectionalLight : public Light {
 private:
  math::vec3 m_InvertedDirection;

 public:
  DirectionalLight();
  DirectionalLight(math::vec3 invertedDirection, math::vec3 color = math::vec3(1, 1, 1));
  math::vec3 getInvertedDirection() const;
  void setInvertedDirection(math::vec3 const& invertedDirection);
};

}  // namespace engine

}  // namespace orbitals
