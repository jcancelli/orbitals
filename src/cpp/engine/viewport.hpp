#pragma once

#include <string>

namespace orbitals {

namespace engine {

class Viewport {
 private:
  float m_Width;
  float m_Height;

 public:
  float getWidth() const;
  float getHeight() const;
  void setWidth(float width);
  void setHeight(float height);
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