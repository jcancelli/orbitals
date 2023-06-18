#include "light.hpp"

#include "../math/projection_matrix.hpp"
#include "camera.hpp"

namespace orbitals {

namespace engine {

DirectionalLight::DirectionalLight()
    : m_Color(1, 1, 1), m_InvertedDirection(0, 1, 0), m_Camera(m_InvertedDirection, -1, 1, -1, 1) {
  m_Camera.lookAt(0, 0, 0);
}

DirectionalLight::DirectionalLight(math::vec3 invertedDirection, math::vec3 color)
    : m_Color(color),
      m_InvertedDirection(invertedDirection),
      m_Camera(m_InvertedDirection, -1, 1, -1, 1) {
  m_Camera.lookAt(0, 0, 0);
}

math::vec3 DirectionalLight::getColor() const {
  return m_Color;
}

void DirectionalLight::setColor(math::vec3 const& color) {
  m_Color = color;
}

math::vec3 DirectionalLight::getInvertedDirection() const {
  return m_InvertedDirection;
}

void DirectionalLight::setInvertedDirection(math::vec3 const& invertedDirection) {
  m_InvertedDirection = invertedDirection;
  m_Camera.setPosition(m_InvertedDirection);
}

OrthograficCamera const& DirectionalLight::getCamera() const {
  return m_Camera;
}

void DirectionalLight::setEffectedVolume(float left, float right, float bottom, float top) {
  m_Camera.setLeft(left);
  m_Camera.setRight(right);
  m_Camera.setBottom(bottom);
  m_Camera.setTop(top);
}

}  // namespace engine

}  // namespace orbitals
