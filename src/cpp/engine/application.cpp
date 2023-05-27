#include "application.hpp"

#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "primitives/debug.hpp"

namespace orbitals {

namespace engine {

Application::Application(std::string const& canvasID) {
  // Init WebGL context
  using namespace std::string_literals;  // for ""s operator
  EmscriptenWebGLContextAttributes ctxAttributes;
  emscripten_webgl_init_context_attributes(&ctxAttributes);
  std::string htmlSelector = "#"s + canvasID;
  m_WebGLContext = emscripten_webgl_create_context(htmlSelector.c_str(), &ctxAttributes);
  emscripten_webgl_make_context_current(m_WebGLContext);
  std::cout << "--------------------------------------------------\n";
  std::cout << glGetString(GL_VERSION) << "\n";
  glCall(glEnable(GL_DEPTH_TEST));

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGui_ImplOpenGL3_Init("#version 300 es");

  // Setup viewport
  m_Viewport = std::shared_ptr<Viewport>(new HTMLCanvasViewport(canvasID));
  m_Viewport->addResizeListener([](float width, float height) {
    ImGui::GetIO().DisplaySize.x = width;
    ImGui::GetIO().DisplaySize.y = height;
  });
  ImGui::GetIO().DisplaySize.x = m_Viewport->getWidth();
  ImGui::GetIO().DisplaySize.y = m_Viewport->getHeight();

  // Setup inputs
  m_Inputs = std::shared_ptr<Inputs>(new Inputs);
  m_Inputs->addKeyDownListener(
      [](Key key) { ImGui::GetIO().AddKeyEvent(keyToImGuiKey(key), true); });
  m_Inputs->addKeyUpListener(
      [](Key key) { ImGui::GetIO().AddKeyEvent(keyToImGuiKey(key), false); });
  m_Inputs->addMouseDownListener(
      [](Mouse::Button button) { ImGui::GetIO().AddMouseButtonEvent(button, true); });
  m_Inputs->addMouseUpListener(
      [](Mouse::Button button) { ImGui::GetIO().AddMouseButtonEvent(button, false); });
  m_Inputs->addMouseMoveListener([](float x, float y) { ImGui::GetIO().AddMousePosEvent(x, y); });
  m_Inputs->addWheelListener([](float scroll) { ImGui::GetIO().AddMouseWheelEvent(0, scroll); });

  m_Clock = std::shared_ptr<Clock>(new Clock);
  m_Clock->addOnTickListener(
      [](Clock const& clock) { ImGui::GetIO().DeltaTime = clock.delta() / 1000; });
}

Application::~Application() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui::DestroyContext();
}

void Application::start() {
  m_IsRunning = EM_TRUE;
  emscripten_request_animation_frame_loop(cycleWrapper, this);
}

void Application::stop() {
  m_IsRunning = EM_FALSE;
}

void Application::setScene(std::shared_ptr<Scene> scene) {
  m_Scene = scene;
}

std::shared_ptr<Viewport const> Application::getViewport() const {
  return m_Viewport;
}

std::shared_ptr<Clock const> Application::getClock() const {
  return m_Clock;
}

std::shared_ptr<Inputs> Application::getInputs() {
  return m_Inputs;
}

void Application::onUpdate() {
}

EM_BOOL Application::cycle(double elapsed) {
  m_Clock->tick(elapsed);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();
  m_Scene->handleInput(m_Inputs->getEvents(), m_Inputs->getKeyboard(), m_Inputs->getMouse());
  m_Scene->update(m_Clock->delta());
  onUpdate();
  glCall(glClearColor(1, 1, 1, 1));
  glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  m_Scene->draw(m_Viewport);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  m_Inputs->clear();
  return m_IsRunning;
}

EM_BOOL Application::cycleWrapper(double elapsed, void* userData) {
  return ((Application*)userData)->cycle(elapsed);
}

EMSCRIPTEN_BINDINGS(application) {
  emscripten::class_<Application>("Application")
      .constructor<std::string>()
      .function("start", &Application::start)
      .function("stop", &Application::stop);
}

}  // namespace engine

}  // namespace orbitals
