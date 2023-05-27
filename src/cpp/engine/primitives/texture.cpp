#include "texture.hpp"

#include "../debug.hpp"

namespace orbitals {

namespace engine {

Texture::Texture() {
  // caches the max texture image units value needed for validation during setActive
  GLint maxVertexTextureUnits, maxFragmentTextureUnits;
  glCall(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxFragmentTextureUnits));
  glCall(glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureUnits));
  MAX_TEXTURE_UNITS = std::min(maxFragmentTextureUnits, maxVertexTextureUnits);
  glCall(glGenTextures(1, &m_Id));
}

void Texture::setActive(GLenum index) const {
  assert(index - GL_TEXTURE0 < MAX_TEXTURE_UNITS);
  glCall(glActiveTexture(index));
}

Texture::~Texture() {
  glCall(glDeleteTextures(1, &m_Id));
}

void Texture2D::bind() const {
  glCall(glBindTexture(GL_TEXTURE_2D, m_Id));
}

void Texture2D::unbind() const {
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

}  // namespace engine

}  // namespace orbitals
