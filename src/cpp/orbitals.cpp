#include <emscripten/bind.h>

#include <memory>

#include "engine/application.hpp"
#include "sample_scene.hpp"

namespace orbitals {

class Orbitals : public engine::Application {
 public:
  Orbitals() {
    setScene(std::shared_ptr<SampleScene>(new SampleScene));
  }

  void onUpdate() override {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowBgAlpha(0.5f);
    ImGui::Begin("#", (bool*)nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
    ImGui::Text("Delta: %f", getClock()->delta());
    ImGui::End();
  }
};

EMSCRIPTEN_BINDINGS(orbitals) {
  emscripten::class_<Orbitals, emscripten::base<engine::Application>>("Orbitals").constructor();
}

}  // namespace orbitals
