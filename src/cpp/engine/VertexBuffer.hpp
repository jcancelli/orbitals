#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "Vertex.hpp"

namespace orbitals {

namespace engine {

class VertexBuffer {
 private:
  GLuint m_Id;

 public:
  VertexBuffer(std::vector<Vertex> const& vertices, GLenum usage);
  ~VertexBuffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
};

}  // namespace engine

}  // namespace orbitals