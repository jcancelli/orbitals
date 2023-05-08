#pragma once

#include <string>

#include "shader.hpp"

namespace orbitals {

namespace engine {

class Material {
 private:
  Shader m_Shader;

 public:
  Material(std::string const& vertShaderSrc, std::string const& fragShaderSrc);
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  Shader& getShader();
};

}  // namespace engine

}  // namespace orbitals
