#include "texture.hpp"

#include <stb/stb_image.h>

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

std::shared_ptr<Texture2D> load_texture2d_from_file(std::string const& path) {
  int width, height, n;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(path.c_str(), &width, &height, &n, 4);
  std::vector<unsigned long> dataVector((unsigned long*)data,
                                        (unsigned long*)(data) + width * height);
  std::shared_ptr<Texture2D> texture(
      new Texture2D(width, height, dataVector, GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE));
  stbi_image_free(data);
  return texture;
}

}  // namespace engine

}  // namespace orbitals
