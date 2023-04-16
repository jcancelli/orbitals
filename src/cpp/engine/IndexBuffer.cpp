#include "IndexBuffer.hpp"

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

IndexBuffer::IndexBuffer(GLuint const* data, unsigned int count, GLenum usage = GL_STATIC_DRAW) {
  glCall(glGenBuffers(1, &m_Id));
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * count, data, usage));
}

IndexBuffer::~IndexBuffer() {
  glCall(glDeleteBuffers(1, &m_Id));
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