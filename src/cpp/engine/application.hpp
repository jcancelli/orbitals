#pragma once

#include <emscripten/html5.h>

#include <memory>
#include <vector>

#include "clock.hpp"
#include "io/keyboard.hpp"
#include "io/mouse.hpp"
#include "io/viewport.hpp"
#include "renderer.hpp"
#include "scene.hpp"

namespace orbitals {

namespace engine {

class Application {
 protected:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_WebGLContext;
  EM_BOOL m_IsRunning;
  std::vector<Event> m_Events;
  std::shared_ptr<Clock> m_Clock;
  std::shared_ptr<Scene> m_Scene;
  std::shared_ptr<Renderer> m_Renderer;

 public:
  Application();
  ~Application();
  void start();
  void stop();
  void setScene(std::shared_ptr<Scene> scene);
  std::shared_ptr<Clock const> getClock() const;
  virtual void onUpdate();

 private:
  EM_BOOL cycle(double elapsed);
  static EM_BOOL cycleWrapper(double elapsed, void* userData);
};

}  // namespace engine

}  // namespace orbitals
