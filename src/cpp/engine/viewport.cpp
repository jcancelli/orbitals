#include "viewport.hpp"

#include <emscripten/html5.h>

#include <iostream>

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
}

void Viewport::setHeight(float height) {
  m_Height = height;
}

float Viewport::aspectRatio() const {
  return m_Width / m_Height;
}

HTMLCanvasViewport::HTMLCanvasViewport(std::string const &canvasHTMLId)
    : m_CanvasHTMLId(canvasHTMLId) {
  emscripten_set_resize_callback(
      EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE,
      [](int eventType, const EmscriptenUiEvent *uiEvent, void *userData) {
        Viewport *vp = (Viewport *)userData;
        vp->setHeight(uiEvent->windowInnerHeight);
        vp->setWidth(uiEvent->windowInnerWidth);
        std::cout << vp->getHeight() << " " << vp->getWidth() << "\n";
        return EM_FALSE;
      });
}
HTMLCanvasViewport::~HTMLCanvasViewport() {
  emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, this, EM_FALSE, nullptr);
}

std::string HTMLCanvasViewport::getCanvasHTMLId() const {
  return m_CanvasHTMLId;
}

}  // namespace engine

}  // namespace orbitals