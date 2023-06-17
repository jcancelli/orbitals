#pragma once

#include <string>

#include "../event.hpp"
#include "../util/listeners_manager.hpp"

namespace orbitals {

namespace engine {

class Viewport {
 private:
  static Viewport s_Instance;
  float m_Width{0};
  float m_Height{0};
  util::Listeners<Event> m_EventListeners;
  util::Listeners<float, float> m_ResizeListeners;

 private:
  Viewport();
  ~Viewport();

 public:
  static Viewport& getInstance();
  float getWidth() const;
  float getHeight() const;
  float aspectRatio() const;
  unsigned addEventListener(util::Listeners<Event>::Listener const& listener);
  void removeEventListener(unsigned listenerID);
  unsigned addResizeListener(util::Listeners<float, float>::Listener const& listener);
  void removeResizeListener(unsigned listenerID);

 private:
  static EM_BOOL resizeCallback(int eventType, const EmscriptenUiEvent* uiEvent, void* userData);
  void setWidth(float width);
  void setHeight(float height);
};

}  // namespace engine

}  // namespace orbitals