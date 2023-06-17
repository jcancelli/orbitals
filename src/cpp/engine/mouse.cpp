#include "mouse.hpp"

#include <cassert>

namespace orbitals {

namespace engine {

Mouse::Mouse() {
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE,
                                Mouse::clickCallback);
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE,
                                    Mouse::downCallback);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE,
                                  Mouse::upCallback);
  emscripten_set_dblclick_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE,
                                   Mouse::dblclickCallback);
  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE,
                                    Mouse::moveCallback);
  emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE,
                                Mouse::wheelCallback);
}

Mouse::~Mouse() {
  emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_dblclick_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_mousemove_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
  emscripten_set_wheel_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
}

Mouse& Mouse::getInstance() {
  return s_Instance;
}

math::vec2 Mouse::getPosition() const {
  return math::vec2(m_X, m_Y);
}

double Mouse::getX() const {
  return m_X;
}

double Mouse::getY() const {
  return m_Y;
}

bool Mouse::isDown(Button button) const {
  switch (button) {
    case Button::Left:
      return m_IsLeftDown;
    case Button::Middle:
      return m_IsMiddleDown;
    case Button::Right:
      return m_IsRightDown;
    default:
      assert(false);
  }
}

bool Mouse::isLeftDown() const {
  return m_IsLeftDown;
}

bool Mouse::isMiddleDown() const {
  return m_IsMiddleDown;
}

bool Mouse::isRightDown() const {
  return m_IsRightDown;
}

unsigned Mouse::addEventListener(util::Listeners<Event>::Listener const& listener) {
  return m_EventListeners.add(listener);
}

void Mouse::removeEventListener(unsigned listenerID) {
  m_EventListeners.remove(listenerID);
}

unsigned Mouse::addOnButtonUpListener(util::Listeners<Button>::Listener const& listener) {
  return m_ButtonUpListeners.add(listener);
}

void Mouse::removeOnButtonUpListener(unsigned listenerID) {
  m_ButtonUpListeners.remove(listenerID);
}

unsigned Mouse::addOnButtonDownListener(util::Listeners<Button>::Listener const& listener) {
  return m_ButtonDownListeners.add(listener);
}

void Mouse::removeOnButtonDownListener(unsigned listenerID) {
  m_ButtonDownListeners.remove(listenerID);
}

unsigned Mouse::addOnMoveListener(util::Listeners<float, float>::Listener const& listener) {
  return m_MoveListeners.add(listener);
}

void Mouse::removeOnMoveListener(unsigned listenerID) {
  m_MoveListeners.remove(listenerID);
}

unsigned Mouse::addOnWheelListener(util::Listeners<float>::Listener const& listener) {
  return m_WheelListeners.add(listener);
}

void Mouse::removeOnWheelListener(unsigned listenerID) {
  m_WheelListeners.remove(listenerID);
}

void Mouse::setPosition(double x, double y) {
  assert(x >= 0);
  assert(y >= 0);
  m_X = x;
  m_Y = y;
}
void Mouse::press(Button button) {
  switch (button) {
    case Button::Left:
      m_IsLeftDown = true;
      break;
    case Button::Middle:
      m_IsMiddleDown = true;
      break;
    case Button::Right:
      m_IsRightDown = true;
      break;
    default:
      assert(false);
  }
}

void Mouse::release(Button button) {
  switch (button) {
    case Button::Left:
      m_IsLeftDown = false;
      break;
    case Button::Middle:
      m_IsMiddleDown = false;
      break;
    case Button::Right:
      m_IsRightDown = false;
      break;
    default:
      assert(false);
  }
}

EM_BOOL Mouse::clickCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData) {
  Mouse& mouse = Mouse::getInstance();
  Event event = {.type = (Event::Type)eventType, .mouse = *emEvent};
  mouse.m_EventListeners.notify(event);
  return EM_FALSE;
}

EM_BOOL Mouse::downCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData) {
  Mouse& mouse = Mouse::getInstance();
  Event event = {.type = (Event::Type)eventType, .mouse = *emEvent};
  Button button = (Button)emEvent->button;
  mouse.press(button);
  mouse.m_EventListeners.notify(event);
  mouse.m_ButtonDownListeners.notify(button);
  return EM_FALSE;
}

EM_BOOL Mouse::upCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData) {
  Mouse& mouse = Mouse::getInstance();
  Event event = {.type = (Event::Type)eventType, .mouse = *emEvent};
  Button button = (Button)emEvent->button;
  mouse.release(button);
  mouse.m_EventListeners.notify(event);
  mouse.m_ButtonUpListeners.notify(button);
  return EM_FALSE;
}

EM_BOOL Mouse::dblclickCallback(int eventType, const EmscriptenMouseEvent* emEvent,
                                void* userData) {
  Mouse& mouse = Mouse::getInstance();
  Event event = {.type = (Event::Type)eventType, .mouse = *emEvent};
  mouse.m_EventListeners.notify(event);
  return EM_FALSE;
}

EM_BOOL Mouse::moveCallback(int eventType, const EmscriptenMouseEvent* emEvent, void* userData) {
  Mouse& mouse = Mouse::getInstance();
  Event event = {.type = (Event::Type)eventType, .mouse = *emEvent};
  mouse.setPosition(emEvent->clientX, emEvent->clientY);
  mouse.m_EventListeners.notify(event);
  mouse.m_MoveListeners.notify(emEvent->clientX, emEvent->clientY);
  return EM_FALSE;
}

EM_BOOL Mouse::wheelCallback(int eventType, const EmscriptenWheelEvent* emEvent, void* userData) {
  Mouse& mouse = Mouse::getInstance();
  Event event = {.type = (Event::Type)eventType, .wheel = *emEvent};
  mouse.m_EventListeners.notify(event);
  mouse.m_WheelListeners.notify(emEvent->deltaY);
  return EM_FALSE;
}

}  // namespace engine

}  // namespace orbitals
