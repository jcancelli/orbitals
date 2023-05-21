#include "inputs.hpp"

#include <boost/algorithm/string.hpp>

namespace orbitals {

namespace engine {

EM_BOOL Inputs::keyboard_event_callback(int type, const EmscriptenKeyboardEvent* emEvent,
                                        void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)type, .keyboard = *emEvent};

  switch (event.type) {
    case Inputs::Event::Type::KeyDown:
      inputs->m_Keyboard.press(browserStringToKey(emEvent->key));
      break;
    case Inputs::Event::Type::KeyUp:
      inputs->m_Keyboard.release(browserStringToKey(emEvent->key));
      break;
    default:
      // do nothing
      break;
  }

  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_event_callback(int type, const EmscriptenMouseEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)type, .mouse = *emEvent};

  switch (event.type) {
    case Inputs::Event::Type::MouseDown:
      inputs->m_Mouse.press((Mouse::Button)emEvent->button);
      break;
    case Inputs::Event::Type::MouseUp:
      inputs->m_Mouse.release((Mouse::Button)emEvent->button);
      break;
    case Inputs::Event::Type::MouseMove:
      inputs->m_Mouse.setPosition(emEvent->clientX, emEvent->clientY);
      break;
    default:
      // do nothing
      break;
  }

  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::wheel_event_callback(int type, const EmscriptenWheelEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)type, .wheel = *emEvent};
  inputs->push(event);
  return EM_FALSE;
}

Inputs::Inputs() {
  // keyboard
  emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                   keyboard_event_callback);
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                  keyboard_event_callback);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                keyboard_event_callback);
  // mouse
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                mouse_event_callback);
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                    mouse_event_callback);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                  mouse_event_callback);
  emscripten_set_dblclick_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                   mouse_event_callback);
  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                    mouse_event_callback);
  emscripten_set_mouseenter_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                     mouse_event_callback);
  emscripten_set_mouseleave_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                     mouse_event_callback);
  // wheel
  emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                wheel_event_callback);
}

Inputs::~Inputs() {
  // keyboard
  emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  // mouse
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_dblclick_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseenter_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseleave_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  // wheel
  emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
}

void Inputs::clear() {
  m_Events.clear();
}

std::vector<Inputs::Event> const& Inputs::getEvents() const {
  return m_Events;
}

Keyboard const& Inputs::getKeyboard() const {
  return m_Keyboard;
}

Mouse const& Inputs::getMouse() const {
  return m_Mouse;
}

void Inputs::push(Event event) {
  m_Events.push_back(event);
}

}  // namespace engine

}  // namespace orbitals
