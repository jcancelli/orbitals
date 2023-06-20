#include "orbital.hpp"

#include <cassert>

#include "../engine/io/viewport.hpp"

namespace orbitals {

namespace widget {

static const double width = 200;
static const double height = 150;
static const double x = -width;
static const double y = 0;

OrbitalWidget::OrbitalWidget()
    : Widget::Widget(x, y, width, height, "Orbitals"), m_N{1}, m_L{0}, m_M{0} {
  setWindowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoFocusOnAppearing);
}

OrbitalWidget::OrbitalWidget(int n, int l, int m)
    : Widget::Widget(x, y, width, height, "Orbitals"), m_N{n}, m_L{l}, m_M{m} {
  assert(n > 0);
  assert(l < n && l >= 0);
  assert(m >= -l && m <= l);
  setWindowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoFocusOnAppearing);
}

void OrbitalWidget::drawContent() {
  ImGui::SliderInt("N", &m_N, 1, 3, nullptr);
  ImGui::SliderInt("L", &m_L, 0, m_N - 1, nullptr);
  ImGui::SliderInt("M", &m_M, -m_L, m_L, nullptr);
  keepNumbersInBouds();

  ImGui::ColorEdit3("Color", m_Color.data(), ImGuiColorEditFlags_NoInputs);

  if (ImGui::Button("Apply")) {
    m_ApplyPressedListeners.notify(m_N, m_L, m_M, m_Color);
  }
}

unsigned OrbitalWidget::addOnApplyPressedListener(ApplyListener listener) {
  return m_ApplyPressedListeners.add(listener);
}

void OrbitalWidget::removeOnApplyPressedListener(unsigned listenerID) {
  m_ApplyPressedListeners.remove(listenerID);
}

void OrbitalWidget::setN(int n) {
  assert(n > 0);
  m_N = n;
  keepNumbersInBouds();
}

int OrbitalWidget::getN() const {
  return m_N;
}

void OrbitalWidget::setL(int l) {
  assert(l < m_N && l >= 0);
  m_L = l;
  keepNumbersInBouds();
}

int OrbitalWidget::getL() const {
  return m_L;
}

void OrbitalWidget::setM(int m) {
  assert(m >= -m_L && m <= m_L);
  m_M = m;
}

int OrbitalWidget::getM() const {
  return m_M;
}

void OrbitalWidget::setColor(math::vec3 const& color) {
  m_Color = color;
}

math::vec3 OrbitalWidget::getColor() const {
  return m_Color;
}

void OrbitalWidget::keepNumbersInBouds() {
  if (m_L > m_N) {
    m_L = m_N - 1;
  }
  if (m_M > m_L) {
    m_M = m_L;
  } else if (m_M < -m_L) {
    m_M = -m_L;
  }
}

}  // namespace widget

}  // namespace orbitals
