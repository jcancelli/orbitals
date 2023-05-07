#include "Viewport.hpp"

namespace orbitals {

namespace engine {

float Viewport::getWidth() const {
  return m_Width;
}

float Viewport::getHeight() const {
  return m_Height;
}

void Viewport::setWidth(float width) {
  m_Width = width;
}

void Viewport::setHeight(float height) {
  m_Height = height;
}

float Viewport::aspectRatio() const {
  return m_Width / m_Height;
}

}  // namespace engine

}  // namespace orbitals