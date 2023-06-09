#include "viewport.hpp"

#include <GLES3/gl3.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "primitives/debug.hpp"

namespace orbitals {

namespace engine {

float Viewport::getWidth() const {
  return m_Width;
}

float Viewport::getHeight() const {
  return m_Height;
}

void Viewport::setWidth(float width) {
  m_Width = width;
  glCall(glViewport(0, 0, m_Width, m_Height));
  m_ResizeListeners.notify(m_Width, m_Height);
}

void Viewport::setHeight(float height) {
  m_Height = height;
  glCall(glViewport(0, 0, m_Width, m_Height));
  m_ResizeListeners.notify(m_Width, m_Height);
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

EM_JS(int, _getHTMLCanvasWidth, (char const *HTMLCanvasId),
      { return document.getElementById(UTF8ToString(HTMLCanvasId)).width; });
EM_JS(int, _getHTMLCanvasHeight, (char const *HTMLCanvasId),
      { return document.getElementById(UTF8ToString(HTMLCanvasId)).height; });

HTMLCanvasViewport::HTMLCanvasViewport(std::string const &canvasHTMLId)
    : m_CanvasHTMLId(canvasHTMLId) {
  emscripten_set_resize_callback(
      EMSCRIPTEN_EVENT_TARGET_WINDOW, this, EM_FALSE,
      [](int eventType, const EmscriptenUiEvent *uiEvent, void *userData) {
        Viewport *vp = (Viewport *)userData;
        vp->setHeight(uiEvent->windowInnerHeight);
        vp->setWidth(uiEvent->windowInnerWidth);
        return EM_FALSE;
      });
  setWidth(_getHTMLCanvasWidth(canvasHTMLId.c_str()));
  setHeight(_getHTMLCanvasHeight(canvasHTMLId.c_str()));
}
HTMLCanvasViewport::~HTMLCanvasViewport() {
  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE, nullptr);
}

std::string HTMLCanvasViewport::getCanvasHTMLId() const {
  return m_CanvasHTMLId;
}

}  // namespace engine

}  // namespace orbitals