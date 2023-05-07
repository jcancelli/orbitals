#pragma once

#include <emscripten.h>

#include <string>

#include "engine/camera.hpp"
#include "engine/input_events.hpp"
#include "engine/viewport.hpp"

namespace orbitals {

class Orbitals {
 private:
  engine::Viewport m_Viewport;
  engine::Camera m_Camera;
  engine::InputEvents m_InputEvents;

 public:
  Orbitals(std::string const& viewportHTMLId);
  void setViewportWidth(float width);
  void setViewportHeight(float height);
  EM_BOOL cycle(double time);
};

}  // namespace orbitals