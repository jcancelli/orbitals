#include "application.hpp"

#include <GLES3/gl3.h>
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>

#include "primitives/debug.hpp"

namespace orbitals {

namespace engine {

Application::Application() {
  // Init WebGL context
  EmscriptenWebGLContextAttributes ctxAttributes;
  emscripten_webgl_init_context_attributes(&ctxAttributes);
  m_WebGLContext = emscripten_webgl_create_context("#viewport", &ctxAttributes);
  emscripten_webgl_make_context_current(m_WebGLContext);
  std::cout << "[webgl] - context created: " << glGetString(GL_VERSION) << "\n";
  glCall(glEnable(GL_DEPTH_TEST));

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui::StyleColorsDark();
  ImGui_ImplOpenGL3_Init("#version 300 es");

  // Setup viewport
  Viewport& viewport = Viewport::getInstance();
  viewport.addResizeListener([](float width, float height) {
    ImGui::GetIO().DisplaySize.x = width;
    ImGui::GetIO().DisplaySize.y = height;
  });
  ImGui::GetIO().DisplaySize.x = viewport.getWidth();
  ImGui::GetIO().DisplaySize.y = viewport.getHeight();
  viewport.addEventListener([this](Event event) { this->m_Events.push_back(event); });

  // Setup keyboard
  Keyboard& keyboard = Keyboard::getInstance();
  keyboard.addKeyDownListener(
      [](Key key) { ImGui::GetIO().AddKeyEvent(keyToImGuiKey(key), true); });
  keyboard.addKeyUpListener([](Key key) { ImGui::GetIO().AddKeyEvent(keyToImGuiKey(key), false); });
  keyboard.addEventListener([this](Event event) { this->m_Events.push_back(event); });

  // setup mouse
  Mouse& mouse = Mouse::getInstance();
  mouse.addOnButtonDownListener(
      [](Mouse::Button button) { ImGui::GetIO().AddMouseButtonEvent(button, true); });
  mouse.addOnButtonUpListener(
      [](Mouse::Button button) { ImGui::GetIO().AddMouseButtonEvent(button, false); });
  mouse.addOnMoveListener([](float x, float y) { ImGui::GetIO().AddMousePosEvent(x, y); });
  mouse.addOnWheelListener([](float scroll) { ImGui::GetIO().AddMouseWheelEvent(0, scroll); });
  mouse.addEventListener([this](Event event) { this->m_Events.push_back(event); });

  m_Clock = std::shared_ptr<Clock>(new Clock);
  m_Clock->addOnTickListener(
      [](Clock const& clock) { ImGui::GetIO().DeltaTime = clock.delta() / 1000; });

  // instantiate renderer
  m_Renderer = std::shared_ptr<Renderer>(new Renderer);
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

std::shared_ptr<Clock const> Application::getClock() const {
  return m_Clock;
}

void Application::onUpdate() {
}

EM_BOOL Application::cycle(double elapsed) {
  m_Clock->tick(elapsed);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui::NewFrame();
  m_Renderer->handleEvents(m_Events);
  m_Scene->handleEvents(m_Events);
  m_Scene->update(m_Clock->delta());
  onUpdate();
  m_Scene->draw(m_Renderer);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  m_Events.clear();
  return m_IsRunning;
}

EM_BOOL Application::cycleWrapper(double elapsed, void* userData) {
  return ((Application*)userData)->cycle(elapsed);
}

EMSCRIPTEN_BINDINGS(application) {
  emscripten::class_<Application>("Application")
      .constructor()
      .function("start", &Application::start)
      .function("stop", &Application::stop);
}

}  // namespace engine

}  // namespace orbitals
