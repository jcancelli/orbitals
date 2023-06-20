#include "debug.hpp"

#include <imgui/imgui.h>

namespace orbitals {

namespace widget {

DebugWidget::DebugWidget() : Widget::Widget(0, 0, 120, 50) {
  setWindowFlags(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
}

void DebugWidget::drawContent() {
  ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
  //   ImGui::Text("Delta: %f", getClock()->delta());
}

}  // namespace widget

}  // namespace orbitals
