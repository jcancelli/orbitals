#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "VertexLayout.hpp"

namespace orbitals {

namespace engine {

class VertexBuffer {
 private:
  GLuint m_Id;
  VertexLayout m_VertexLayout;

 public:
  template <class VertexT>  // VertexT must have a ::layout static property of type VertexLayout
  VertexBuffer(std::vector<VertexT> const& vertices, GLenum usage = GL_STATIC_DRAW);
  ~VertexBuffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
  VertexLayout const& getVertexLayout() const;
};

}  // namespace engine

}  // namespace orbitals