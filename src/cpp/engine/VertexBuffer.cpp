#include "VertexBuffer.hpp"

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

template <class VertexT>
VertexBuffer::VertexBuffer(std::vector<VertexT> const& vertices, GLenum usage)
    : m_VertexLayout{VertexT::layout} {
  glCall(glGenBuffers(1, &m_Id));
  glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(VertexT) * vertices.size(), vertices.data(), usage));
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

VertexLayout const& VertexBuffer::getVertexLayout() const {
  return m_VertexLayout;
}

}  // namespace engine

}  // namespace orbitals