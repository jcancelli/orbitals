#pragma once

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

}  // namespace engine

}  // namespace orbitals