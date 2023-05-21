#include "keyboard.hpp"

#include <emscripten/html5.h>

#include <boost/algorithm/string.hpp>
#include <cassert>

namespace orbitals {

namespace engine {

static std::unordered_map<std::string, Key> browserStringToKeyMap{
    {"CONTROL", Ctrl},           //
    {"SHIFT", Shift},            //
    {"CAPSLOCK", CapsLock},      //
    {"TAB", Tab},                //
    {"ALT", Alt},                //
    {"SPACE", Space},            //
    {"ENTER", Enter},            //
    {"DELETE", Delete},          //
    {"ESC", Esc},                //
    {"ARROWLEFT", ArrowLeft},    //
    {"ARROWUP", ArrowUp},        //
    {"ARROWDOWN", ArrowDown},    //
    {"ARROWRIGHT", ArrowRight},  //
    {"F1", F1},                  //
    {"F2", F2},                  //
    {"F3", F3},                  //
    {"F4", F4},                  //
    {"F5", F5},                  //
    {"F6", F6},                  //
    {"F7", F7},                  //
    {"F8", F8},                  //
    {"F9", F9},                  //
    {"F1", F1},                  //
    {"F10", F10},                //
    {"F11", F11},                //
    {"F12", F12},                //
    {"1", Num1},                 //
    {"2", Num2},                 //
    {"3", Num3},                 //
    {"4", Num4},                 //
    {"5", Num5},                 //
    {"6", Num6},                 //
    {"7", Num7},                 //
    {"8", Num8},                 //
    {"9", Num9},                 //
    {"0", Num0},                 //
    {"Q", Q},                    //
    {"W", W},                    //
    {"E", E},                    //
    {"R", R},                    //
    {"T", T},                    //
    {"Y", Y},                    //
    {"U", U},                    //
    {"I", I},                    //
    {"O", O},                    //
    {"P", P},                    //
    {"A", A},                    //
    {"S", S},                    //
    {"D", D},                    //
    {"F", F},                    //
    {"G", G},                    //
    {"H", H},                    //
    {"J", J},                    //
    {"K", K},                    //
    {"L", L},                    //
    {"Z", Z},                    //
    {"X", X},                    //
    {"C", C},                    //
    {"V", V},                    //
    {"B", B},                    //
    {"N", N},                    //
    {"M", M}                     //
};                               //

static std::unordered_map<Key, ImGuiKey> keyToImGuiKeyMap{
    {Ctrl, ImGuiKey_LeftCtrl},          //
    {Shift, ImGuiKey_LeftShift},        //
    {CapsLock, ImGuiKey_CapsLock},      //
    {Tab, ImGuiKey_Tab},                //
    {Alt, ImGuiKey_LeftAlt},            //
    {Space, ImGuiKey_Space},            //
    {Enter, ImGuiKey_Enter},            //
    {Delete, ImGuiKey_Delete},          //
    {Esc, ImGuiKey_Escape},             //
    {ArrowLeft, ImGuiKey_LeftArrow},    //
    {ArrowUp, ImGuiKey_UpArrow},        //
    {ArrowDown, ImGuiKey_DownArrow},    //
    {ArrowRight, ImGuiKey_RightArrow},  //
    {F1, ImGuiKey_F1},                  //
    {F2, ImGuiKey_F2},                  //
    {F3, ImGuiKey_F3},                  //
    {F4, ImGuiKey_F4},                  //
    {F5, ImGuiKey_F5},                  //
    {F6, ImGuiKey_F6},                  //
    {F7, ImGuiKey_F7},                  //
    {F8, ImGuiKey_F8},                  //
    {F9, ImGuiKey_F9},                  //
    {F10, ImGuiKey_F10},                //
    {F11, ImGuiKey_F11},                //
    {F12, ImGuiKey_F12},                //
    {Num0, ImGuiKey_0},                 //
    {Num1, ImGuiKey_1},                 //
    {Num2, ImGuiKey_2},                 //
    {Num3, ImGuiKey_3},                 //
    {Num4, ImGuiKey_4},                 //
    {Num5, ImGuiKey_5},                 //
    {Num6, ImGuiKey_6},                 //
    {Num7, ImGuiKey_7},                 //
    {Num8, ImGuiKey_8},                 //
    {Num9, ImGuiKey_9},                 //
    {Q, ImGuiKey_Q},                    //
    {W, ImGuiKey_W},                    //
    {E, ImGuiKey_E},                    //
    {R, ImGuiKey_R},                    //
    {T, ImGuiKey_T},                    //
    {Y, ImGuiKey_Y},                    //
    {U, ImGuiKey_U},                    //
    {I, ImGuiKey_I},                    //
    {O, ImGuiKey_O},                    //
    {P, ImGuiKey_P},                    //
    {A, ImGuiKey_A},                    //
    {S, ImGuiKey_S},                    //
    {D, ImGuiKey_D},                    //
    {F, ImGuiKey_F},                    //
    {G, ImGuiKey_G},                    //
    {H, ImGuiKey_H},                    //
    {J, ImGuiKey_J},                    //
    {K, ImGuiKey_K},                    //
    {L, ImGuiKey_L},                    //
    {Z, ImGuiKey_Z},                    //
    {X, ImGuiKey_X},                    //
    {C, ImGuiKey_C},                    //
    {V, ImGuiKey_V},                    //
    {B, ImGuiKey_B},                    //
    {N, ImGuiKey_N},                    //
    {M, ImGuiKey_M}                     //
};                                      //

Key browserStringToKey(std::string key) {
  std::transform(key.begin(), key.end(), key.begin(), ::toupper);
  auto pos = browserStringToKeyMap.find(key);
  if (pos == browserStringToKeyMap.end()) {
    return Key::Unmapped;
  }
  return browserStringToKeyMap[key];
}

ImGuiKey keyToImGuiKey(Key key) {
  return keyToImGuiKeyMap[key];
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
