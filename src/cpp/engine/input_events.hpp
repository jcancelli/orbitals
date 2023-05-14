#pragma once

#include <emscripten/html5.h>

#include <queue>
#include <string>

namespace orbitals {

namespace engine {

struct InputEvent {
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
    BackSpace = 8,
    Tab = 9,
    Enter = 13,
    Shift = 16,
    Ctrl = 17,
    Alt = 18,
    CapsLock = 20,
    Esc = 27,
    Space = 32,
    PageUp = 33,
    PageDown = 34,
    Home = 36,
    ArrowLeft = 37,
    ArrowUp = 38,
    ArrowRight = 39,
    ArrowDown = 40,
    PrintScreen = 44,
    Insert = 45,
    Delete = 46,
    Num0 = 48,
    Num1 = 49,
    Num2 = 50,
    Num3 = 51,
    Num4 = 52,
    Num5 = 53,
    Num6 = 54,
    Num7 = 55,
    Num8 = 56,
    Num9 = 57,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LeftMeta = 91,
    RightMeta = 92,
    Select = 93,
    NumPad0 = 96,
    NumPad1 = 97,
    NumPad2 = 98,
    NumPad3 = 99,
    NumPad4 = 100,
    NumPad5 = 101,
    NumPad6 = 102,
    NumPad7 = 103,
    NumPad8 = 104,
    NumPad9 = 105,
    F1 = 112,
    F2 = 113,
    F3 = 114,
    F4 = 115,
    F5 = 116,
    F6 = 117,
    F7 = 118,
    F8 = 119,
    F9 = 120,
    F10 = 121,
    F11 = 122,
    F12 = 123,
    SemiColon = 186,
    Equal = 187,
    Comma = 188,
    Dash = 189,
    Period = 190,
    Slash = 191,
    OpenBracket = 219,
    BackSlash = 220,
    CloseBracket = 221,
    SingleQuote = 222
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
  std::queue<InputEvent> m_Events;
  char const* m_Target;

 public:
  InputEvents(char const* target);
  ~InputEvents();
  void push(InputEvent& event);
  InputEvent next();
  InputEvent const& peek() const;
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
