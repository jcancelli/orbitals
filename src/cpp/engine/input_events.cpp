#include "input_events.hpp"

#include <emscripten/html5.h>

#include <unordered_map>

namespace orbitals {

namespace engine {

EM_BOOL keyboard_event_callback(int type, const EmscriptenKeyboardEvent* emEvent, void* userData) {
  InputEvent event = {.type = (InputEvent::Type)type, .keyboard = *emEvent};
  ((InputEvents*)userData)->push(event);
  return EM_FALSE;
}

EM_BOOL mouse_event_callback(int type, const EmscriptenMouseEvent* emEvent, void* userData) {
  InputEvent event = {.type = (InputEvent::Type)type, .mouse = *emEvent};
  ((InputEvents*)userData)->push(event);
  return EM_FALSE;
}

EM_BOOL wheel_event_callback(int type, const EmscriptenWheelEvent* emEvent, void* userData) {
  InputEvent event = {.type = (InputEvent::Type)type, .wheel = *emEvent};
  ((InputEvents*)userData)->push(event);
  return EM_FALSE;
}

InputEvents::InputEvents(char const* target) : m_Target(target) {
  // keyboard
  emscripten_set_keypress_callback(target, this, EM_FALSE, keyboard_event_callback);
  emscripten_set_keydown_callback(target, this, EM_FALSE, keyboard_event_callback);
  emscripten_set_keyup_callback(target, this, EM_FALSE, keyboard_event_callback);
  // mouse
  emscripten_set_click_callback(target, this, EM_FALSE, mouse_event_callback);
  emscripten_set_mousedown_callback(target, this, EM_FALSE, mouse_event_callback);
  emscripten_set_mouseup_callback(target, this, EM_FALSE, mouse_event_callback);
  emscripten_set_dblclick_callback(target, this, EM_FALSE, mouse_event_callback);
  emscripten_set_mousemove_callback(target, this, EM_FALSE, mouse_event_callback);
  emscripten_set_mouseenter_callback(target, this, EM_FALSE, mouse_event_callback);
  emscripten_set_mouseleave_callback(target, this, EM_FALSE, mouse_event_callback);
  // wheel
  emscripten_set_wheel_callback(target, this, EM_FALSE, wheel_event_callback);
}

InputEvents::~InputEvents() {
  // keyboard
  emscripten_set_keypress_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_keydown_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_keyup_callback(m_Target, nullptr, EM_FALSE, nullptr);
  // mouse
  emscripten_set_click_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_mousedown_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseup_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_dblclick_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_mousemove_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseenter_callback(m_Target, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseleave_callback(m_Target, nullptr, EM_FALSE, nullptr);
  // wheel
  emscripten_set_wheel_callback(m_Target, nullptr, EM_FALSE, nullptr);
}

InputEvent InputEvents::next() {
  InputEvent event = m_Events.front();
  m_Events.pop();
  return event;
}

InputEvent const& InputEvents::peek() const {
  return m_Events.front();
}

bool InputEvents::isEmpty() const {
  return m_Events.empty();
}

void InputEvents::push(InputEvent& event) {
  m_Events.push(event);
}

}  // namespace engine

}  // namespace orbitals
