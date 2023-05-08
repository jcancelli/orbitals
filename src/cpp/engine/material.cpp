#pragma once

#include "material.hpp"

namespace orbitals {

namespace engine {

Material::Material(std::string const& vertShaderSrc, std::string const& fragShaderSrc)
    : m_Shader(vertShaderSrc, fragShaderSrc) {
}

Shader& Material::getShader() {
  return m_Shader;
}

}  // namespace engine

}  // namespace orbitals
