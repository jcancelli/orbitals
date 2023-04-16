#pragma once

#include <GLES3/gl3.h>

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

namespace orbitals {

namespace engine {

class VertexArray {
 private:
  GLuint m_Id;

 public:
  VertexArray(VertexBuffer const& vbo, VertexBufferLayout const& layout);
  ~VertexArray();
  void bind() const;
  void unbind() const;
};

}  // namespace engine

}  // namespace orbitals
