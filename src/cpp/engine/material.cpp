#include "material.hpp"

#include "../util/fs.hpp"

namespace orbitals {

namespace engine {

Material::Material(std::string const& vertShaderSrc, std::string const& fragShaderSrc)
    : m_Shader(vertShaderSrc, fragShaderSrc) {
}

Shader& Material::getShader() {
  return m_Shader;
}

BasicMaterial::BasicMaterial()
    : Material::Material(util::read_string("./shaders/basic.vert"),
                         util::read_string("./shaders/basic.frag")),
      m_Color(0.988, 0.059, 0.753),
      m_Shinyness{2} {
}

BasicMaterial::BasicMaterial(float r, float g, float b, float shinyness)
    : Material::Material(util::read_string("./shaders/basic.vert"),
                         util::read_string("./shaders/basic.frag")),
      m_Color(r, g, b),
      m_Shinyness{shinyness} {
}

BasicMaterial::BasicMaterial(math::vec3 const& color, float shinyness)
    : Material::Material(util::read_string("./shaders/basic.vert"),
                         util::read_string("./shaders/basic.frag")),
      m_Color(color),
      m_Shinyness{shinyness} {
}

void BasicMaterial::bind() {
  m_Shader.bind();
  m_Shader.setUniform3f("uDiffuseColor", m_Color);
  m_Shader.setUniform1f("uShinyness", m_Shinyness);
}

void BasicMaterial::unbind() {
  m_Shader.unbind();
}

void BasicMaterial::setColor(math::vec3 const& color) {
  m_Color = color;
}

math::vec3 BasicMaterial::getColor() const {
  return m_Color;
}

void BasicMaterial::setShinyness(float shinyness) {
  m_Shinyness = shinyness;
}

float BasicMaterial::getShinyness() const {
  return m_Shinyness;
}

}  // namespace engine

}  // namespace orbitals
