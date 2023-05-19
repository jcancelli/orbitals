#pragma once

#include <vector>

#include "buffer.hpp"
#include "transform.hpp"
#include "vertex.hpp"
#include "vertex_layout.hpp"

namespace orbitals {

namespace engine {

template <class TVertex>  // TVertex must have a ::layout static property of type VertexLayout
class GenericVertexBuffer : public Buffer<TVertex> {
 private:
  VertexLayout m_VertexLayout;

 public:
  GenericVertexBuffer(std::vector<TVertex> const& vertices, GLenum usage = GL_STATIC_DRAW);
  VertexLayout const& getVertexLayout() const;
};

using VertexBuffer = GenericVertexBuffer<Vertex>;
// using TransformsBuffer = GenericVertexBuffer<Transform>;

}  // namespace engine

}  // namespace orbitals

#include "vertex_buffer.inl"