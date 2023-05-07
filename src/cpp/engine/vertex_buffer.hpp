#pragma once

#include <vector>

#include "buffer.hpp"
#include "vertex_layout.hpp"

namespace orbitals {

namespace engine {

class VertexBuffer : public Buffer {
 private:
  VertexLayout m_VertexLayout;

 public:
  template <class TVertex>  // TVertex must have a ::layout static property of type VertexLayout
  VertexBuffer(std::vector<TVertex> const& vertices, GLenum usage = GL_STATIC_DRAW);
  VertexLayout const& getVertexLayout() const;
};

}  // namespace engine

}  // namespace orbitals