#include "light.hpp"

#include "../math/projection_matrix.hpp"
#include "camera.hpp"

namespace orbitals {

namespace engine {

Light::Light() : m_Color(1, 1, 1) {
}

Light::Light(math::vec3 color) : m_Color(color) {
}

math::vec3 Light::getColor() const {
  return m_Color;
}

void Light::setColor(math::vec3 const& color) {
  m_Color = color;
}

DirectionalLight::DirectionalLight() : m_InvertedDirection(0, 1, 0) {
}

DirectionalLight::DirectionalLight(math::vec3 invertedDirection, math::vec3 color)
    : Light::Light(color), m_InvertedDirection(invertedDirection) {
}
math::vec3 DirectionalLight::getInvertedDirection() const {
  return m_InvertedDirection;
}

void DirectionalLight::setInvertedDirection(math::vec3 const& invertedDirection) {
  m_InvertedDirection = invertedDirection;
}

}  // namespace engine

}  // namespace orbitals
