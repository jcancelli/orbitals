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

 public:
  template <class TData>
  Buffer(GLenum target, std::vector<TData> const& data, GLenum usage) : m_Target(target) {
    glCall(glGenBuffers(1, &m_Id));
    glCall(glBindBuffer(target, m_Id));
    glCall(glBufferData(target, sizeof(TData) * data.size(), data.data(), usage));
    glCall(glBindBuffer(target, 0));
  }
  ~Buffer();
  void bind() const;
  void unbind() const;
  GLuint id() const;
  GLenum target() const;
};

}  // namespace engine

}  // namespace orbitals