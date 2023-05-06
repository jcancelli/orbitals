#pragma once

#include "Shader.hpp"

namespace orbitals {

namespace engine {

class Drawable {
 public:
  virtual void draw(Shader const& shader) const {};
};

}  // namespace engine

}  // namespace orbitals
