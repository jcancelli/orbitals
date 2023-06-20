#pragma once

#include <imgui/imgui.h>

#include <string>

#include "../math/vector.hpp"

namespace orbitals {

namespace widget {

class Widget {
 protected:
  math::vec2 m_Position;
  math::vec2 m_Size;
  std::string m_Title;
  ImGuiWindowFlags m_WindowFlags;

 public:
  Widget();
  Widget(float x, float y, float width, float height, std::string const& title = "##");
  Widget(math::vec2 const& position, math::vec2 const& size, std::string const& title = "##");
  void draw();
  void setPosition(math::vec2 const& position);
  math::vec2 getPosition() const;
  void setSize(math::vec2 const& size);
  math::vec2 getSize() const;
  void setWindowFlags(ImGuiWindowFlags flags);
  ImGuiWindowFlags getWindowFlags() const;

 protected:
  virtual void drawContent() = 0;
};

}  // namespace widget

}  // namespace orbitals
