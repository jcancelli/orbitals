#include "widget.hpp"

#include <cassert>

#include "../engine/io/viewport.hpp"

namespace orbitals {

namespace widget {

Widget::Widget() : m_Position(0, 0), m_Size(0, 0), m_Title{"##"}, m_WindowFlags{0} {
}

Widget::Widget(float x, float y, float width, float height, std::string const& title)
    : m_Position(x, y), m_Size(width, height), m_Title{title}, m_WindowFlags{0} {
  assert(width >= 0);
  assert(height >= 0);
}

Widget::Widget(math::vec2 const& position, math::vec2 const& size, std::string const& title)
    : m_Position(position), m_Size(size), m_Title{title}, m_WindowFlags{0} {
  assert(size[0] >= 0);
  assert(size[1] >= 0);
}

void Widget::draw() {
  ImGui::SetNextWindowBgAlpha(.6);
  ImGui::Begin(m_Title.c_str(), nullptr, m_WindowFlags);
  ImGui::SetWindowSize(m_Size);
  math::vec2 pos = m_Position;
  if (pos[0] < 0) {
    pos[0] = engine::Viewport::getInstance().getWidth() + pos[0];
  }
  if (pos[1] < 0) {
    pos[1] = engine::Viewport::getInstance().getHeight() + pos[1];
  }
  ImGui::SetWindowPos(pos);
  drawContent();
  ImGui::End();
}

void Widget::setPosition(math::vec2 const& position) {
  m_Position = position;
}

math::vec2 Widget::getPosition() const {
  return m_Position;
}

void Widget::setSize(math::vec2 const& size) {
  assert(size[0] >= 0);
  assert(size[1] >= 0);
  m_Size = size;
}

math::vec2 Widget::getSize() const {
  return m_Size;
}

void Widget::setWindowFlags(ImGuiWindowFlags flags) {
  m_WindowFlags = flags;
}

ImGuiWindowFlags Widget::getWindowFlags() const {
  return m_WindowFlags;
}

}  // namespace widget

}  // namespace orbitals
