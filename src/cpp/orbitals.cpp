#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>

#include <cassert>
#include <iostream>
#include <string>

#include "engine/camera.hpp"
#include "engine/debug.hpp"
#include "engine/input_events.hpp"
#include "engine/viewport.hpp"

namespace orbitals {

using namespace std::string_literals;  // for ""s operator

class Orbitals {
 private:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_WebGLContext;
  EM_BOOL m_IsExecuting;
  std::shared_ptr<engine::HTMLCanvasViewport> m_Viewport;
  std::shared_ptr<engine::InputEvents> m_InputEvents;

 public:
  Orbitals(std::string const& viewportHTMLId)
      : m_WebGLContext(initWebGLContext(viewportHTMLId)),
        m_IsExecuting{EM_FALSE},
        m_Viewport(new engine::HTMLCanvasViewport(viewportHTMLId)),
        m_InputEvents(new engine::InputEvents(EMSCRIPTEN_EVENT_TARGET_DOCUMENT)) {
  }

  void start() {
    m_IsExecuting = EM_TRUE;
    emscripten_request_animation_frame_loop(cycleWrapper, this);
  }

  void stop() {
    m_IsExecuting = EM_FALSE;
  }

 private:
  EM_BOOL cycle(double time) {
    return m_IsExecuting;
  }

  static EM_BOOL cycleWrapper(double time, void* userData) {
    return ((Orbitals*)userData)->cycle(time);
  }

  static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE initWebGLContext(std::string const& viewportHTMLId) {
    EmscriptenWebGLContextAttributes ctxAttributes;
    emscripten_webgl_init_context_attributes(&ctxAttributes);
    std::string htmlCanvasSelector = "#"s + viewportHTMLId;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx =
        emscripten_webgl_create_context(htmlCanvasSelector.c_str(), &ctxAttributes);
    emscripten_webgl_make_context_current(ctx);
    std::cout << glGetString(GL_VERSION) << "\n";
    glCall(glEnable(GL_DEPTH_TEST));
    return ctx;
  }
};

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals>("Orbitals")
      .constructor<std::string>()
      .function("start", &Orbitals::start)
      .function("stop", &Orbitals::stop);
}

}  // namespace orbitals