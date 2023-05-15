#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "debug.hpp"

namespace orbitals {

namespace engine {

class Buffer {
 private:
  GLuint m_Id;
  GLenum m_Target;
  GLsizei m_Size;

 public:
  template <class TData>
  Buffer(GLenum target, std::vector<TData> const& data, GLenum usage)
      : m_Target(target), m_Size(sizeof(TData) * data.size()) {
    glCall(glGenBuffers(1, &m_Id));
    glCall(glBindBuffer(target, m_Id));
    glCall(glBufferData(target, m_Size, data.data(), usage));
    glCall(glBindBuffer(target, 0));
  }
  ~Buffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
  GLenum target() const;
  GLsizei size() const;
};

}  // namespace engine

}  // namespace orbitals