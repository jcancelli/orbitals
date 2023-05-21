#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "../imgui/imgui.h"

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
 protected:
  std::unordered_map<Key, bool> m_State;

 public:
  bool keyIsDown(Key const& key) const;
  std::vector<Key> getDownKeys() const;
  void press(Key const& key);
  void release(Key const& key);
};

}  // namespace engine

}  // namespace orbitals
