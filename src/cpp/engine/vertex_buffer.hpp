#pragma once

#include <vector>

#include "buffer.hpp"
#include "transform.hpp"
#include "vertex.hpp"
#include "vertex_layout.hpp"

namespace orbitals {

namespace engine {

template <class T>  // T must have a ::layout static property of type VertexLayout
class VertexBuffer : public Buffer<T> {
 private:
  VertexLayout m_VertexLayout;

 public:
  VertexBuffer(std::vector<T> const& data, GLenum usage = GL_STATIC_DRAW);
  VertexLayout const& getVertexLayout() const;
};

using VertexDataBuffer = VertexBuffer<Vertex>;
using VertexTransformsBuffer = VertexBuffer<Transform>;

}  // namespace engine

}  // namespace orbitals

#include "vertex_buffer.inl"