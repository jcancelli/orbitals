#pragma once

#include <emscripten/html5.h>

#include "../math/vector.hpp"
#include "../util/listeners_manager.hpp"
#include "event.hpp"

namespace orbitals {

namespace engine {

class Mouse {
 public:
  enum Button { Left = 0, Middle = 1, Right = 2 };

 private:
  static Mouse s_Instance;
  double m_X, m_Y;
  bool m_IsLeftDown, m_IsMiddleDown, m_IsRightDown;
  util::Listeners<Event> m_EventListeners;  // listeners for all the mouse events
  util::Listeners<Button> m_ButtonDownListeners;
  util::Listeners<Button> m_ButtonUpListeners;
  util::Listeners<float, float> m_MoveListeners;
  util::Listeners<float> m_WheelListeners;

 private:
  Mouse();
  ~Mouse();

 public:
  static Mouse& getInstance();
  math::vec2 getPosition() const;
  double getX() const;
  double getY() const;
  bool isDown(Button button) const;
  bool isLeftDown() const;
  bool isMiddleDown() const;
  bool isRightDown() const;
  unsigned addEventListener(util::Listeners<Event>::Listener const& listener);
  void removeEventListener(unsigned listenerID);
  unsigned addOnButtonUpListener(util::Listeners<Button>::Listener const& listener);
  void removeOnButtonUpListener(unsigned listenerID);
  unsigned addOnButtonDownListener(util::Listeners<Button>::Listener const& listener);
  void removeOnButtonDownListener(unsigned listenerID);
  unsigned addOnMoveListener(util::Listeners<float, float>::Listener const& listener);
  void removeOnMoveListener(unsigned listenerID);
  unsigned addOnWheelListener(util::Listeners<float>::Listener const& listener);
  void removeOnWheelListener(unsigned listenerID);

 private:
  void setPosition(double x, double y);
  void press(Button button);
  void release(Button button);
  static EM_BOOL clickCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData);
  static EM_BOOL downCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData);
  static EM_BOOL upCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData);
  static EM_BOOL dblclickCallback(int eventType, const EmscriptenMouseEvent* emEvent,
                                  void* userData);
  static EM_BOOL moveCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData);
  static EM_BOOL wheelCallback(int emEventType, const EmscriptenWheelEvent* emEvent,
                               void* userData);
};

}  // namespace engine

}  // namespace orbitals
