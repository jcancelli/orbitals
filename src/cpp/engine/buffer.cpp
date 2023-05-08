#include "buffer.hpp"

#include "debug.hpp"

namespace orbitals {

namespace engine {

Buffer::~Buffer() {
  glCall(glDeleteBuffers(1, &m_Id));
}

void Buffer::bind() const {
  glCall(glBindBuffer(m_Target, m_Id));
}

void Buffer::unbind() const {
  glCall(glBindBuffer(m_Target, 0));
}

GLuint Buffer::id() const {
  return m_Id;
}

GLenum Buffer::target() const {
  return m_Target;
}

}  // namespace engine

}  // namespace orbitals