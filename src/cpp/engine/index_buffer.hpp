#pragma once

#include <GLES3/gl3.h>

#include <vector>

namespace orbitals {

namespace engine {

class IndexBuffer {
 private:
  GLuint m_Id;
  std::size_t m_Count;

 public:
  IndexBuffer(std::vector<GLuint> const& indices, GLenum usage);
  ~IndexBuffer();
  GLsizei getPrimitivesCount(GLenum type) const;
  std::size_t getCount() const;
  void bind() const;
  void unbind() const;
  GLuint id() const;
};

}  // namespace engine

}  // namespace orbitals