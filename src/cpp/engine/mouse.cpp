#include "mouse.hpp"

#include <cassert>

namespace orbitals {

namespace engine {

void Mouse::setX(double x) {
  assert(x >= 0);
  m_X = x;
}

double Mouse::getX() const {
  return m_X;
}

void Mouse::setY(double y) {
  assert(y >= 0);
  m_Y = y;
}

double Mouse::getY() const {
  return m_Y;
}

void Mouse::setPosition(math::vec2 const& pos) {
  setX(pos.x());
  setY(pos.y());
}

void Mouse::setPosition(double x, double y) {
  setX(x);
  setY(y);
}

math::vec2 Mouse::getPosition() const {
  return math::vec2(m_X, m_Y);
}

void Mouse::setLeftDown(bool isDown) {
  m_IsLeftDown = isDown;
}

bool Mouse::isLeftDown() const {
  return m_IsLeftDown;
}

void Mouse::setMiddleDown(bool isDown) {
  m_IsMiddleDown = isDown;
}

bool Mouse::isMiddleDown() const {
  return m_IsMiddleDown;
}

void Mouse::setRightDown(bool isDown) {
  m_IsRightDown = isDown;
}

bool Mouse::isRightDown() const {
  return m_IsRightDown;
}

}  // namespace engine

}  // namespace orbitals
