#pragma once

#include <emscripten/html5.h>

namespace orbitals {

namespace engine {

struct ViewportEvent {
  float width, height;
};

struct Event {
  enum class Type {
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
    Wheel = EMSCRIPTEN_EVENT_WHEEL,
    Viewport
  };

  Type type;

  union {
    EmscriptenKeyboardEvent keyboard;
    EmscriptenMouseEvent mouse;
    EmscriptenWheelEvent wheel;
    ViewportEvent viewport;
  };
};

}  // namespace engine

}  // namespace orbitals
