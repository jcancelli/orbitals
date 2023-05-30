#include <emscripten/bind.h>

#include <memory>

#include "engine/application.hpp"
#include "sample_scene.hpp"

namespace orbitals {

class Orbitals : public engine::Application {
 public:
  Orbitals(std::string const& canvasID) : Application::Application(canvasID) {
    setScene(std::shared_ptr<SampleScene>(new SampleScene));
  }
  void onUpdate() override {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::Begin("#", (bool*)__null, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text((std::string("FPS: ") + std::to_string(ImGui::GetIO().Framerate)).c_str());
    ImGui::Text((std::string("Delta: ") + std::to_string(getClock()->delta())).c_str());
    ImGui::End();
  }
};

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals, emscripten::base<engine::Application>>("Orbitals")
      .constructor<std::string>();
}

}  // namespace orbitals
