#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "buffer.hpp"

namespace orbitals {

namespace engine {

class IndexBuffer : public Buffer {
 private:
  std::size_t m_Count;

 public:
  IndexBuffer(std::vector<GLuint> const& indices, GLenum usage);
  GLsizei getPrimitivesCount(GLenum type) const;
  std::size_t getCount() const;
};

}  // namespace engine

}  // namespace orbitals