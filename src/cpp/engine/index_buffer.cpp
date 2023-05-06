#include "index_buffer.hpp"

#include <cassert>

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

IndexBuffer::IndexBuffer(std::vector<GLuint> const& indices, GLenum usage = GL_STATIC_DRAW)
    : m_Count{indices.size()} {
  glCall(glGenBuffers(1, &m_Id));
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(),
                      usage));
}

IndexBuffer::~IndexBuffer() {
  glCall(glDeleteBuffers(1, &m_Id));
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

void IndexBuffer::bind() const {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
}

void IndexBuffer::unbind() const {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

GLuint IndexBuffer::id() const {
  return m_Id;
}

}  // namespace engine

}  // namespace orbitals