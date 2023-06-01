#include "texture.hpp"

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

Texture2D::Texture2D(GLsizei width, GLsizei height, GLenum format, GLint internalFormat,
                     GLenum type, GLint minFilter, GLint magFilter, GLint wrapS, GLint wrapR,
                     GLint wrapT, bool genMipmap) {
  bind();
  glCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrapR));
  glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT));
  if (genMipmap) {
    glCall(glGenerateMipmap(GL_TEXTURE_2D));
  }
  unbind();
}

void Texture2D::bind() const {
  glCall(glBindTexture(GL_TEXTURE_2D, m_Id));
}

void Texture2D::unbind() const {
  glCall(glBindTexture(GL_TEXTURE_2D, 0));
}

}  // namespace engine

}  // namespace orbitals
