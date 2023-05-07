#pragma once

#include <GLES3/gl3.h>

#include "vertex_buffer.hpp"

namespace orbitals {

namespace engine {

class VertexArray {
 private:
  GLuint m_Id;

 public:
  VertexArray(VertexBuffer const& vbo);
  ~VertexArray();
  void bind() const;
  void unbind() const;
};

}  // namespace engine

}  // namespace orbitals
