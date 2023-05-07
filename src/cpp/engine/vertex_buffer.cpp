#include "vertex_buffer.hpp"

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

template <class TVertex>
VertexBuffer::VertexBuffer(std::vector<TVertex> const& vertices, GLenum usage)
    : Buffer::Buffer(GL_ARRAY_BUFFER, vertices, usage), m_VertexLayout{TVertex::layout} {
}

VertexLayout const& VertexBuffer::getVertexLayout() const {
  return m_VertexLayout;
}

}  // namespace engine

}  // namespace orbitals