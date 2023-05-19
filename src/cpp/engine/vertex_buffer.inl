#pragma once

#include "debug.hpp"
#include "vertex_buffer.hpp"

namespace orbitals {

namespace engine {

template <class TVertex>
GenericVertexBuffer<TVertex>::GenericVertexBuffer(std::vector<TVertex> const& vertices,
                                                  GLenum usage)
    : Buffer<TVertex>::Buffer(GL_ARRAY_BUFFER, vertices, usage), m_VertexLayout{TVertex::layout} {
}

template <class TVertex>
VertexLayout const& GenericVertexBuffer<TVertex>::getVertexLayout() const {
  return m_VertexLayout;
}

}  // namespace engine

}  // namespace orbitals