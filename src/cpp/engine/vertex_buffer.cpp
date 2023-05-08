#include "vertex_buffer.hpp"

#include "debug.hpp"

namespace orbitals {

namespace engine {

VertexLayout const& VertexBuffer::getVertexLayout() const {
  return m_VertexLayout;
}

}  // namespace engine

}  // namespace orbitals