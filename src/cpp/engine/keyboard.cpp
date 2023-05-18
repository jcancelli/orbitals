#include "keyboard.hpp"

#include <emscripten/html5.h>

#include <boost/algorithm/string.hpp>
#include <cassert>

namespace orbitals {

namespace engine {

bool Keyboard::isDown(std::string const& key) const {
  return m_State.find(key) != m_State.end() && m_State.at(key);
}

std::vector<std::string> Keyboard::getDownKeys() const {
  std::vector<std::string> downKeys;
  for (auto const& keyState : m_State) {
    if (keyState.second) {
      downKeys.push_back(keyState.first);
    }
  }
  return downKeys;
}

void Keyboard::press(std::string const& key) {
  m_State[key] = true;
}

void Keyboard::release(std::string const& key) {
  m_State[key] = false;
}

}  // namespace engine

}  // namespace orbitals
