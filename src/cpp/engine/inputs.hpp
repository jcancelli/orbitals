#pragma once

#include <emscripten/html5.h>

#include <vector>

#include "../util/listeners_manager.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

namespace orbitals {

namespace engine {

class Inputs {
 public:
  struct Event {
    enum Type {
      KeyPressed = EMSCRIPTEN_EVENT_KEYPRESS,
      KeyDown = EMSCRIPTEN_EVENT_KEYDOWN,
      KeyUp = EMSCRIPTEN_EVENT_KEYUP,
      MouseClick = EMSCRIPTEN_EVENT_CLICK,
      MouseDown = EMSCRIPTEN_EVENT_MOUSEDOWN,
      MouseUp = EMSCRIPTEN_EVENT_MOUSEUP,
      MouseDoubleClick = EMSCRIPTEN_EVENT_DBLCLICK,
      MouseMove = EMSCRIPTEN_EVENT_MOUSEMOVE,
      MouseEnter = EMSCRIPTEN_EVENT_MOUSEENTER,
      MouseLeave = EMSCRIPTEN_EVENT_MOUSELEAVE,
      Wheel = EMSCRIPTEN_EVENT_WHEEL
    };

    Type type;

    union {
      EmscriptenKeyboardEvent keyboard;
      EmscriptenMouseEvent mouse;
      EmscriptenWheelEvent wheel;
    };
  };

 private:
  Keyboard m_Keyboard;
  Mouse m_Mouse;
  std::vector<Event> m_Events;
  util::Listeners<Key> m_KeyDownListeners;
  util::Listeners<Key> m_KeyUpListeners;
  util::Listeners<Mouse::Button> m_MouseDownListeners;
  util::Listeners<Mouse::Button> m_MouseUpListeners;
  util::Listeners<float, float> m_MouseMoveListeners;
  util::Listeners<float> m_WheelListeners;
  util::Listeners<std::vector<Event>, Keyboard const&, Mouse const&> m_OnNewFrameListeners;

 public:
  Inputs();
  ~Inputs();
  unsigned addKeyDownListener(util::Listeners<Key>::Listener const& listener);
  void removeKeyDownListener(unsigned listenerID);
  unsigned addKeyUpListener(util::Listeners<Key>::Listener const& listener);
  void removeKeyUpListener(unsigned listenerID);
  unsigned addMouseUpListener(util::Listeners<Mouse::Button>::Listener const& listener);
  void removeMouseUpListener(unsigned listenerID);
  unsigned addMouseDownListener(util::Listeners<Mouse::Button>::Listener const& listener);
  void removeMouseDownListener(unsigned listenerID);
  unsigned addMouseMoveListener(util::Listeners<float, float>::Listener const& listener);
  void removeMouseMoveListener(unsigned listenerID);
  unsigned addWheelListener(util::Listeners<float>::Listener const& listener);
  void removeWheelListener(unsigned listenerID);
  unsigned addOnNewFrameListener(
      util::Listeners<std::vector<Event>, Keyboard const&, Mouse const&>::Listener const& listener);
  void removeOnNewFrameListener(unsigned listenerID);
  void clear();
  std::vector<Event> const& getEvents() const;
  Keyboard const& getKeyboard() const;
  Mouse const& getMouse() const;

 private:
  void push(Event event);
  static EM_BOOL key_down_callback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                   void* userData);
  static EM_BOOL key_up_callback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                 void* userData);
  static EM_BOOL key_pressed_callback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                      void* userData);
  static EM_BOOL mouse_click_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                      void* userData);
  static EM_BOOL mouse_down_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                     void* userData);
  static EM_BOOL mouse_up_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                   void* userData);
  static EM_BOOL mouse_dblclick_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                         void* userData);
  static EM_BOOL mouse_move_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                     void* userData);
  static EM_BOOL mouse_enter_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                      void* userData);
  static EM_BOOL mouse_leave_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                      void* userData);
  static EM_BOOL wheel_event_callback(int emEventType, const EmscriptenWheelEvent* emEvent,
                                      void* userData);
};

}  // namespace engine

}  // namespace orbitals
