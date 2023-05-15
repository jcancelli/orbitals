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

EM_BOOL keyboard_event_callback(int type, const EmscriptenKeyboardEvent* emEvent, void* userData) {
  Keyboard* keyboard = ((Keyboard*)userData);

  char key[32];
  strcpy(key, emEvent->key);
  boost::algorithm::to_upper(key);  // needed because key can be both lowercase and uppercase

  if (type == EMSCRIPTEN_EVENT_KEYDOWN) {
    keyboard->press(key);
  } else if (type == EMSCRIPTEN_EVENT_KEYUP) {
    keyboard->release(key);
  }
  return EM_FALSE;
}

BrowserEventsKeyboard::BrowserEventsKeyboard() {
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                  keyboard_event_callback);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                keyboard_event_callback);
}

BrowserEventsKeyboard::~BrowserEventsKeyboard() {
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
}

}  // namespace engine

}  // namespace orbitals
