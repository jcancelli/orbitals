#include "index_buffer.hpp"

#include <cassert>

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

IndexBuffer::IndexBuffer(std::vector<GLuint> const& indices, GLenum usage = GL_STATIC_DRAW)
    : Buffer::Buffer(GL_ELEMENT_ARRAY_BUFFER, indices, usage), m_Count{indices.size()} {
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
  }
}

std::size_t IndexBuffer::getCount() const {
  return m_Count;
}

}  // namespace engine

}  // namespace orbitals