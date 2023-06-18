#include "viewport.hpp"

#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

namespace orbitals {

namespace engine {

EM_JS(int, _getHTMLCanvasWidth, (), { return document.getElementById("viewport").width; });
EM_JS(int, _getHTMLCanvasHeight, (), { return document.getElementById("viewport").height; });

Viewport Viewport::s_Instance;

Viewport::Viewport() {
  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, nullptr, EM_FALSE,
                                 Viewport::resizeCallback);
  setWidth(_getHTMLCanvasWidth());
  setHeight(_getHTMLCanvasHeight());
}

Viewport::~Viewport() {
  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, nullptr, EM_FALSE, nullptr);
}

Viewport &Viewport::getInstance() {
  return s_Instance;
}

float Viewport::getWidth() const {
  return m_Width;
}

float Viewport::getHeight() const {
  return m_Height;
}

unsigned Viewport::addEventListener(util::Listeners<Event>::Listener const &listener) {
  return m_EventListeners.add(listener);
}

void Viewport::removeEventListener(unsigned listenerID) {
  m_EventListeners.remove(listenerID);
}

unsigned Viewport::addResizeListener(util::Listeners<float, float>::Listener const &listener) {
  return m_ResizeListeners.add(listener);
}

void Viewport::removeResizeListener(unsigned listenerID) {
  m_ResizeListeners.remove(listenerID);
}

float Viewport::aspectRatio() const {
  return m_Width / m_Height;
}

EM_BOOL Viewport::resizeCallback(int eventType, const EmscriptenUiEvent *uiEvent, void *userData) {
  Viewport &viewport = Viewport::getInstance();
  float width = uiEvent->windowInnerWidth;
  float height = uiEvent->windowInnerHeight;
  Event event = {.type = Event::Type::Viewport, .viewport = {width, height}};
  viewport.setWidth(width);
  viewport.setHeight(height);
  viewport.m_EventListeners.notify(event);
  viewport.m_ResizeListeners.notify(width, height);
  return EM_FALSE;
}

void Viewport::setWidth(float width) {
  m_Width = width;
}

void Viewport::setHeight(float height) {
  m_Height = height;
}

}  // namespace engine

}  // namespace orbitals