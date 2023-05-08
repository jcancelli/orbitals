#pragma once

#include <string>

#include "shader.hpp"

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

}  // namespace engine

}  // namespace orbitals
