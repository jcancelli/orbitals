#include "Orbitals.hpp"

#include <emscripten/bind.h>

#include <cassert>

namespace orbitals {

Orbitals::Orbitals() {
}

void Orbitals::setViewportWidth(float width) {
  assert(width > 0);
  m_Viewport.setWidth(width);
}

void Orbitals::setViewportHeight(float height) {
  assert(height > 0);
  m_Viewport.setHeight(height);
}

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals>("Orbitals")
      .constructor()
      .function("setViewportWidth", &Orbitals::setViewportWidth)
      .function("setViewportHeight", &Orbitals::setViewportHeight);
}

}  // namespace orbitals
