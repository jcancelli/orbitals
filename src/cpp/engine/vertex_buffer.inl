#pragma once

#include "debug.hpp"
#include "vertex_buffer.hpp"

namespace orbitals {

namespace engine {

template <class T>
VertexBuffer<T>::VertexBuffer(std::vector<T> const& data, GLenum usage)
    : Buffer<T>::Buffer(GL_ARRAY_BUFFER, data, usage), m_VertexLayout{T::layout} {
}

template <class T>
VertexLayout const& VertexBuffer<T>::getVertexLayout() const {
  return m_VertexLayout;
}

}  // namespace engine

}  // namespace orbitals