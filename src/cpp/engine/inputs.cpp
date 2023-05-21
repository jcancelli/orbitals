#include "inputs.hpp"

#include <iostream>

namespace orbitals {

namespace engine {

EM_BOOL Inputs::key_down_callback(int eventType, const EmscriptenKeyboardEvent* emEvent,
                                  void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .keyboard = *emEvent};
  Key key = browserStringToKey(emEvent->key);
  inputs->m_Keyboard.press(key);
  inputs->push(event);
  inputs->m_KeyDownListeners.notify(key);
  return EM_FALSE;
}

EM_BOOL Inputs::key_up_callback(int eventType, const EmscriptenKeyboardEvent* emEvent,
                                void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .keyboard = *emEvent};
  Key key = browserStringToKey(emEvent->key);
  inputs->m_Keyboard.release(key);
  inputs->push(event);
  inputs->m_KeyUpListeners.notify(key);
  return EM_FALSE;
}

EM_BOOL Inputs::key_pressed_callback(int eventType, const EmscriptenKeyboardEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .keyboard = *emEvent};
  Key key = browserStringToKey(emEvent->key);
  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_click_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_down_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                    void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  Mouse::Button button = (Mouse::Button)emEvent->button;
  inputs->m_Mouse.press(button);
  inputs->push(event);
  inputs->m_MouseDownListeners.notify(button);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_up_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                  void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  Mouse::Button button = (Mouse::Button)emEvent->button;
  inputs->m_Mouse.release(button);
  inputs->push(event);
  inputs->m_MouseUpListeners.notify(button);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_dblclick_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                        void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_move_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                    void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  inputs->push(event);
  inputs->m_MouseMoveListeners.notify(emEvent->clientX, emEvent->clientY);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_enter_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::mouse_leave_callback(int eventType, const EmscriptenMouseEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .mouse = *emEvent};
  inputs->push(event);
  return EM_FALSE;
}

EM_BOOL Inputs::wheel_event_callback(int eventType, const EmscriptenWheelEvent* emEvent,
                                     void* userData) {
  Inputs* inputs = (Inputs*)userData;
  Inputs::Event event = {.type = (Inputs::Event::Type)eventType, .wheel = *emEvent};
  inputs->push(event);
  inputs->m_WheelListeners.notify(emEvent->deltaY);
  return EM_FALSE;
}

Inputs::Inputs() {
  // keyboard
  emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                   key_pressed_callback);
  emscripten_set_keydown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                  key_down_callback);
  emscripten_set_keyup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE, key_up_callback);
  // mouse
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                mouse_click_callback);
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                    mouse_down_callback);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                  mouse_up_callback);
  emscripten_set_dblclick_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                   mouse_dblclick_callback);
  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                    mouse_move_callback);
  emscripten_set_mouseenter_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                     mouse_enter_callback);
  emscripten_set_mouseleave_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
                                     mouse_leave_callback);
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

unsigned Inputs::addKeyDownListener(util::Listeners<Key>::Listener const& listener) {
  return m_KeyDownListeners.add(listener);
}

void Inputs::removeKeyDownListener(unsigned listenerID) {
  m_KeyDownListeners.remove(listenerID);
}

unsigned Inputs::addKeyUpListener(util::Listeners<Key>::Listener const& listener) {
  return m_KeyUpListeners.add(listener);
}

void Inputs::removeKeyUpListener(unsigned listenerID) {
  m_KeyUpListeners.remove(listenerID);
}

unsigned Inputs::addMouseUpListener(util::Listeners<Mouse::Button>::Listener const& listener) {
  return m_MouseUpListeners.add(listener);
}

void Inputs::removeMouseUpListener(unsigned listenerID) {
  m_MouseUpListeners.remove(listenerID);
}

unsigned Inputs::addMouseDownListener(util::Listeners<Mouse::Button>::Listener const& listener) {
  return m_KeyDownListeners.add(listener);
}

void Inputs::removeMouseDownListener(unsigned listenerID) {
  m_KeyDownListeners.remove(listenerID);
}

unsigned Inputs::addMouseMoveListener(util::Listeners<float, float>::Listener const& listener) {
  return m_MouseMoveListeners.add(listener);
}

void Inputs::removeMouseMoveListener(unsigned listenerID) {
  m_MouseMoveListeners.remove(listenerID);
}

unsigned Inputs::addWheelListener(util::Listeners<float>::Listener const& listener) {
  return m_WheelListeners.add(listener);
}

void Inputs::removeWheelListener(unsigned listenerID) {
  m_WheelListeners.remove(listenerID);
}
unsigned Inputs::addOnNewFrameListener(
    util::Listeners<std::vector<Event>, Keyboard const&, Mouse const&>::Listener const& listener) {
  return m_OnNewFrameListeners.add(listener);
}

void Inputs::removeOnNewFrameListener(unsigned listenerID) {
  m_OnNewFrameListeners.remove(listenerID);
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
