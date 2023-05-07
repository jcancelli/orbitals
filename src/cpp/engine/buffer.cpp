#include "buffer.hpp"

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

template <class TData>
Buffer::Buffer(GLenum target, std::vector<TData> const& data, GLenum usage) : m_Target(target) {
  glCall(glGenBuffers(1, &m_Id));
  glCall(glBufferData(target, sizeof(TData) * data.size(), data.data(), usage));
}

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