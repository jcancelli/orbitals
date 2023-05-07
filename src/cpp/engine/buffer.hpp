#pragma once

#include <GLES3/gl3.h>

#include <vector>

namespace orbitals {

namespace engine {

class Buffer {
 private:
  GLuint m_Id;
  GLenum m_Target;

 public:
  template <class TData>
  Buffer(GLenum target, std::vector<TData> const& data, GLenum usage);
  ~Buffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
  GLenum target() const;
};

}  // namespace engine

}  // namespace orbitals