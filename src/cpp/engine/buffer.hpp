#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "debug.hpp"

namespace orbitals {

namespace engine {

template <class T>
class Buffer {
 private:
  GLuint m_Id;
  GLenum m_Target;
  std::vector<T> m_Data;  // CPU side copy of data

 public:
  Buffer(GLenum target, std::vector<T> const& data, GLenum usage);
  ~Buffer();
  void bind() const;
  void unbind() const;
  void write(std::vector<T> const& data, unsigned to = 0);
  void write(T const& data, unsigned to = 0);
  T read(unsigned from) const;
  GLuint id() const;
  GLenum target() const;
  GLsizei size() const;
  std::size_t count() const;
};

}  // namespace engine

}  // namespace orbitals

#include "buffer.inl"