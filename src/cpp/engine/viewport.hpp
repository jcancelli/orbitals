#pragma once

#include <string>

#include "../util/listeners_manager.hpp"

namespace orbitals {

namespace engine {

class Viewport {
 private:
  float m_Width{0};
  float m_Height{0};
  util::Listeners<float, float> m_ResizeListeners;

 public:
  float getWidth() const;
  float getHeight() const;
  void setWidth(float width);
  void setHeight(float height);
  unsigned addResizeListener(util::Listeners<float, float>::Listener const& listener);
  void removeResizeListener(unsigned listenerID);
  float aspectRatio() const;
};

class HTMLCanvasViewport : public Viewport {
 private:
  std::string m_CanvasHTMLId;

 public:
  HTMLCanvasViewport(std::string const& canvasHTMLId);
  ~HTMLCanvasViewport();
  std::string getCanvasHTMLId() const;
};

}  // namespace engine

}  // namespace orbitals