#include "keyboard.hpp"

#include <emscripten/html5.h>

#include <boost/algorithm/string.hpp>
#include <cassert>

namespace orbitals {

namespace engine {

static std::unordered_map<std::string, Key> browserStringToKeyMap{
    {"CONTROL", Ctrl},            //
    {"SHIFT", Shift},             //
    {"BLOCKMAIUS", BlockMaiusc},  //
    {"TAB", Tab},                 //
    {"ALT", Alt},                 //
    {"SPACE", Space},             //
    {"ENTER", Enter},             //
    {"DELETE", Delete},           //
    {"ESC", Esc},                 //
    {"ARROWLEFT", ArrowLeft},     //
    {"ARROWUP", ArrowUp},         //
    {"ARROWDOWN", ArrowDown},     //
    {"ARROWRIGHT", ArrowRight},   //
    {"F1", F1},                   //
    {"F2", F2},                   //
    {"F3", F3},                   //
    {"F4", F4},                   //
    {"F5", F5},                   //
    {"F6", F6},                   //
    {"F7", F7},                   //
    {"F8", F8},                   //
    {"F9", F9},                   //
    {"F1", F1},                   //
    {"F10", F10},                 //
    {"F11", F11},                 //
    {"F12", F12},                 //
    {"1", Num1},                  //
    {"2", Num2},                  //
    {"3", Num3},                  //
    {"4", Num4},                  //
    {"5", Num5},                  //
    {"6", Num6},                  //
    {"7", Num7},                  //
    {"8", Num8},                  //
    {"9", Num9},                  //
    {"0", Num0},                  //
    {"Q", Q},                     //
    {"W", W},                     //
    {"E", E},                     //
    {"R", R},                     //
    {"T", T},                     //
    {"Y", Y},                     //
    {"U", U},                     //
    {"I", I},                     //
    {"O", O},                     //
    {"P", P},                     //
    {"A", A},                     //
    {"S", S},                     //
    {"D", D},                     //
    {"F", F},                     //
    {"G", G},                     //
    {"H", H},                     //
    {"J", J},                     //
    {"K", K},                     //
    {"L", L},                     //
    {"Z", Z},                     //
    {"X", X},                     //
    {"C", C},                     //
    {"V", V},                     //
    {"B", B},                     //
    {"N", N},                     //
    {"M", M}                      //
};                                //

Key browserStringToKey(std::string key) {
  std::transform(key.begin(), key.end(), key.begin(), ::toupper);
  auto pos = browserStringToKeyMap.find(key);
  if (pos == browserStringToKeyMap.end()) {
    return Key::Unmapped;
  }
  return browserStringToKeyMap[key];
}

bool Keyboard::keyIsDown(Key const& key) const {
  return m_State.find(key) != m_State.end() && m_State.at(key);
}

std::vector<Key> Keyboard::getDownKeys() const {
  std::vector<Key> downKeys;
  for (auto const& [key, isDown] : m_State) {
    if (isDown) {
      downKeys.push_back(key);
    }
  }
  return downKeys;
}

void Keyboard::press(Key const& key) {
  m_State[key] = true;
}

void Keyboard::release(Key const& key) {
  m_State[key] = false;
}

}  // namespace engine

}  // namespace orbitals
