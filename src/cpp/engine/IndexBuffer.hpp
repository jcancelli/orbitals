#pragma once

#include <GLES3/gl3.h>

namespace engine {

class IndexBuffer {
 private:
  GLuint m_Id;

 public:
  IndexBuffer(GLuint const* data, unsigned int count, GLenum usage);
  ~IndexBuffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
};

}  // namespace engine