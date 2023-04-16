#pragma once

#include <GLES3/gl3.h>

namespace engine {

class VertexBuffer {
 private:
  GLuint m_Id;

 public:
  VertexBuffer(void const* data, GLsizeiptr size, GLenum usage);
  ~VertexBuffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
};

}  // namespace engine