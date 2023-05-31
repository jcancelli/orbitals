#pragma once

#include <cassert>
#include <vector>

#include "debug.hpp"
#include "gl_object.hpp"

namespace orbitals {

namespace engine {

class Texture : public GLObject {
 private:
  GLint MAX_TEXTURE_UNITS;

 public:
  Texture();
  ~Texture();
  virtual void bind() const = 0;
  virtual void unbind() const = 0;
  void setActive(GLenum index) const;
};

class Texture2D : public Texture {
 public:
  template <class T>
  Texture2D(GLsizei width, GLsizei height, std::vector<T> const& data, GLenum format,
            GLint internalFormat, GLenum type, GLint minFilter = GL_LINEAR,
            GLint magFilter = GL_LINEAR, GLint wrapS = GL_CLAMP_TO_EDGE,
            GLint wrapR = GL_CLAMP_TO_EDGE, GLint wrapT = GL_CLAMP_TO_EDGE,
            bool genMipmap = false) {
    assert(data.size() == width * height);
    bind();
    glCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type,
                        data.data()));
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
  Texture2D(GLsizei width, GLsizei height, GLenum format, GLint internalFormat, GLenum type,
            GLint minFilter = GL_LINEAR, GLint magFilter = GL_LINEAR,
            GLint wrapS = GL_CLAMP_TO_EDGE, GLint wrapR = GL_CLAMP_TO_EDGE,
            GLint wrapT = GL_CLAMP_TO_EDGE, bool genMipmap = false);
  void bind() const override;
  void unbind() const override;
};

}  // namespace engine

}  // namespace orbitals
