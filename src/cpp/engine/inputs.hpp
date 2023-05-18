#pragma once

#include <emscripten/html5.h>

#include <vector>

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

 public:
  Inputs();
  ~Inputs();
  void clear();
  std::vector<Event> const& getEvents() const;
  Keyboard const& getKeyboard() const;
  Mouse const& getMouse() const;

 private:
  void push(Event event);
  static EM_BOOL keyboard_event_callback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                         void* userData);
  static EM_BOOL mouse_event_callback(int emEventType, const EmscriptenMouseEvent* emEvent,
                                      void* userData);
  static EM_BOOL wheel_event_callback(int emEventType, const EmscriptenWheelEvent* emEvent,
                                      void* userData);
};

}  // namespace engine

}  // namespace orbitals
