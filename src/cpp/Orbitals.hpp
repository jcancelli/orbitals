#pragma once

#include "engine/Camera.hpp"
#include "engine/Viewport.hpp"

namespace orbitals {

class Orbitals {
 private:
  engine::Viewport m_Viewport;
  engine::Camera m_Camera;

 public:
  Orbitals();
  void setViewportWidth(float width);
  void setViewportHeight(float height);
};

}  // namespace orbitals