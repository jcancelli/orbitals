#pragma once

#include <emscripten/html5.h>

#include <queue>
#include <string>

namespace orbitals {

namespace engine {

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

  enum MouseButton : unsigned short { Left = 0, Middle = 1, Right = 2 };

  enum KeyCode : unsigned long {
    Tab = 9,
    Enter = 13,
    Shift = 16,
    Control = 17,
    Alt = 18,
    Space = 32,
    ArrowLeft = 37,
    ArrowUp = 38,
    ArrowRight = 39,
    ArrowDown = 40
  };

  Type type;

  union {
    EmscriptenKeyboardEvent keyboard;
    EmscriptenMouseEvent mouse;
    EmscriptenWheelEvent wheel;
  };
};

class InputEvents {
 private:
  std::queue<Event> m_Events;
  char const* m_Target;

 public:
  InputEvents(char const* target);
  ~InputEvents();
  void push(Event& event);
  Event next();
  Event const& peek() const;
  bool isEmpty() const;

 private:
  friend EM_BOOL keyboard_event_callback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                         void* userData);
  friend EM_BOOL mouse_event_callback(int emEventType, const EmscriptenMouseEvent* emEvent,
                                      void* userData);
  friend EM_BOOL wheel_event_callback(int emEventType, const EmscriptenWheelEvent* emEvent,
                                      void* userData);
};

}  // namespace engine

}  // namespace orbitals
