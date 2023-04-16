#include "VertexBuffer.hpp"

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

VertexBuffer::VertexBuffer(void const* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW) {
  glCall(glGenBuffers(1, &m_Id));
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

VertexBuffer::~VertexBuffer() {
  glCall(glDeleteBuffers(1, &m_Id));
}

void VertexBuffer::bind() const {
  glCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
}

void VertexBuffer::unbind() const {
  glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

GLuint VertexBuffer::id() const {
  return m_Id;
}

}  // namespace engine

}  // namespace orbitals