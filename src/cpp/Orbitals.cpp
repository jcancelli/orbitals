#include "Orbitals.hpp"

#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>

#include <cassert>
#include <iostream>

#include "engine/glDebug.hpp"

namespace orbitals {

using namespace std::string_literals;  // for ""s operator

static void initWebGLContext(std::string const& viewportHTMLId) {
  EmscriptenWebGLContextAttributes ctxAttributes;
  emscripten_webgl_init_context_attributes(&ctxAttributes);
  std::string htmlCanvasSelector = "#"s + viewportHTMLId;
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx =
      emscripten_webgl_create_context(htmlCanvasSelector.c_str(), &ctxAttributes);
  emscripten_webgl_make_context_current(ctx);
  std::cout << glGetString(GL_VERSION) << std::endl;
  glCall(glEnable(GL_DEPTH_TEST));
}

static EM_BOOL loopCycle(double time, void* userData) {
  return ((Orbitals*)userData)->cycle(time);
}

Orbitals::Orbitals(std::string const& viewportHTMLId) {
  initWebGLContext(viewportHTMLId);
  emscripten_request_animation_frame_loop(loopCycle, this);
}

void Orbitals::setViewportWidth(float width) {
  assert(width > 0);
  m_Viewport.setWidth(width);
}

void Orbitals::setViewportHeight(float height) {
  assert(height > 0);
  m_Viewport.setHeight(height);
}

EM_BOOL Orbitals::cycle(double time) {
  return EM_FALSE;
}

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals>("Orbitals")
      .constructor<std::string>()
      .function("setViewportWidth", &Orbitals::setViewportWidth)
      .function("setViewportHeight", &Orbitals::setViewportHeight);
}

}  // namespace orbitals
