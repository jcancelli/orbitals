#pragma once

#include "engine/Viewport.hpp"

namespace orbitals {

class Orbitals {
 private:
  engine::Viewport m_Viewport;

 public:
  Orbitals();
  void setViewportWidth(float width);
  void setViewportHeight(float height);
};

}  // namespace orbitals