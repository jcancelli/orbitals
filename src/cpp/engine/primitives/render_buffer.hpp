#pragma once

#include "gl_object.hpp"

namespace orbitals {

namespace engine {

class RenderBuffer : public GLObject {
 public:
  RenderBuffer(GLsizei width, GLsizei height, GLenum internalFormat, GLsizei samples = 0);
  ~RenderBuffer();
  void bind() const;
  void unbind() const;
};

}  // namespace engine

}  // namespace orbitals
