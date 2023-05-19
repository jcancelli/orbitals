#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "buffer.hpp"

namespace orbitals {

namespace engine {

class IndexBuffer : public Buffer<GLuint> {
 private:
  std::size_t m_Count;

 public:
  IndexBuffer(std::vector<GLuint> const& indices, GLenum usage = GL_STATIC_DRAW);

  GLsizei getPrimitivesCount(GLenum type) const;
};

}  // namespace engine

}  // namespace orbitals