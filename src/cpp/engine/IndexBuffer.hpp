#pragma once

#include <GLES3/gl3.h>

#include <vector>

namespace orbitals {

namespace engine {

class IndexBuffer {
 private:
  GLuint m_Id;

 public:
  IndexBuffer(std::vector<GLuint> const& indices, GLenum usage);
  ~IndexBuffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
};

}  // namespace engine

}  // namespace orbitals