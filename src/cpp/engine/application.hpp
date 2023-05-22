#pragma once

#include <emscripten/html5.h>

#include <memory>

#include "clock.hpp"
#include "inputs.hpp"
#include "scene.hpp"
#include "viewport.hpp"

namespace orbitals {

namespace engine {

class Application {
 protected:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE m_WebGLContext;
  EM_BOOL m_IsRunning;
  std::shared_ptr<Viewport> m_Viewport;
  std::shared_ptr<Clock> m_Clock;
  std::shared_ptr<Inputs> m_Inputs;
  std::shared_ptr<Scene> m_Scene;

 public:
  Application(std::string const& canvasID);
  ~Application();
  void start();
  void stop();
  void setScene(std::shared_ptr<Scene> scene);
  std::shared_ptr<Viewport const> getViewport() const;
  std::shared_ptr<Clock const> getClock() const;
  std::shared_ptr<Inputs> getInputs();
  virtual void onUpdate();

 private:
  EM_BOOL cycle(double elapsed);
  static EM_BOOL cycleWrapper(double elapsed, void* userData);
};

}  // namespace engine

}  // namespace orbitals
