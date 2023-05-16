#pragma once

#include "../math/vector.hpp"

namespace orbitals {

namespace engine {

class Mouse {
 public:
  enum Button { Left = 0, Middle = 1, Right = 2 };

 private:
  double m_X, m_Y;
  bool m_IsLeftDown, m_IsMiddleDown, m_IsRightDown;

 public:
  void setX(double x);
  double getX() const;
  void setY(double y);
  double getY() const;
  void setPosition(math::vec2 const& pos);
  void setPosition(double x, double y);
  math::vec2 getPosition() const;
  void setLeftDown(bool isDown);
  bool isLeftDown() const;
  void setMiddleDown(bool isDown);
  bool isMiddleDown() const;
  void setRightDown(bool isDown);
  bool isRightDown() const;
};

}  // namespace engine

}  // namespace orbitals
