#include "index_buffer.hpp"

#include <cassert>

#include "debug.hpp"

namespace orbitals {

namespace engine {

IndexBuffer::IndexBuffer(std::vector<GLuint> const& indices, GLenum usage)
    : Buffer<GLuint>::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, usage), m_Count{indices.size()} {
}

GLsizei IndexBuffer::getPrimitivesCount(GLenum type) const {
  switch (type) {
    case GL_TRIANGLES:
      assert(m_Count % 3 == 0);
      return m_Count / 3;
    case GL_LINES:
      assert(m_Count % 2 == 0);
      return m_Count / 2;
    case GL_POINTS:
      return m_Count;
    default:
      assert(false);
  }
}

}  // namespace engine

}  // namespace orbitals