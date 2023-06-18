#pragma once

#include <emscripten/html5.h>
#include <imgui/imgui.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "../../util/listeners_manager.hpp"
#include "../event.hpp"

namespace orbitals {

namespace engine {

enum Key {
  Ctrl,
  Shift,
  CapsLock,
  Tab,
  Alt,
  Space,
  Enter,
  Delete,
  Esc,
  ArrowLeft,
  ArrowUp,
  ArrowDown,
  ArrowRight,
  F1,
  F2,
  F3,
  F4,
  F5,
  F6,
  F7,
  F8,
  F9,
  F10,
  F11,
  F12,
  Num0,
  Num1,
  Num2,
  Num3,
  Num4,
  Num5,
  Num6,
  Num7,
  Num8,
  Num9,
  Q,
  W,
  E,
  R,
  T,
  Y,
  U,
  I,
  O,
  P,
  A,
  S,
  D,
  F,
  G,
  H,
  J,
  K,
  L,
  Z,
  X,
  C,
  V,
  B,
  N,
  M,
  Unmapped
};

Key browserStringToKey(std::string key);
ImGuiKey keyToImGuiKey(Key key);

class Keyboard {
 private:
  static Keyboard s_Instance;
  std::unordered_map<Key, bool> m_State;
  util::Listeners<Event> m_EventListeners;
  util::Listeners<Key> m_KeyDownListeners;
  util::Listeners<Key> m_KeyUpListeners;

 private:
  Keyboard();
  ~Keyboard();

 public:
  static Keyboard& getInstance();
  bool isDown(Key key) const;
  std::vector<Key> getDownKeys() const;
  unsigned addEventListener(util::Listeners<Event>::Listener const& listener);
  void removeEventListener(unsigned listenerID);
  unsigned addKeyDownListener(util::Listeners<Key>::Listener const& listener);
  void removeKeyDownListener(unsigned listenerID);
  unsigned addKeyUpListener(util::Listeners<Key>::Listener const& listener);
  void removeKeyUpListener(unsigned listenerID);

 private:
  static EM_BOOL keyDownCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                 void* userData);
  static EM_BOOL keyUpCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                               void* userData);
  static EM_BOOL keyPressedCallback(int eventType, const EmscriptenKeyboardEvent* keyEvent,
                                    void* userData);
  void press(Key key);
  void release(Key key);
};

}  // namespace engine

}  // namespace orbitals
