#pragma once

#include <string>

#include "../math/vector.hpp"
#include "primitives/shader.hpp"

namespace orbitals {

namespace engine {

class Material {
 protected:
  Shader m_Shader;

 public:
  Material(std::string const& vertShaderSrc, std::string const& fragShaderSrc);
  virtual void bind() = 0;
  virtual void unbind() = 0;
  Shader& getShader();
};

class BasicMaterial : public Material {
 private:
  math::vec3 m_Color;
  float m_Shinyness;

 public:
  BasicMaterial();
  BasicMaterial(float r, float g, float b, float shinyness);
  BasicMaterial(math::vec3 const& color, float shinyness);
  void bind() override;
  void unbind() override;
  void setColor(math::vec3 const& color);
  math::vec3 getColor() const;
  void setShinyness(float shinyness);
  float getShinyness() const;
};

}  // namespace engine

}  // namespace orbitals
