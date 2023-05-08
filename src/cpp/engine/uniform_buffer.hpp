#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "buffer.hpp"

namespace orbitals {

namespace engine {

template <class T>
class UniformBuffer : public Buffer {
 private:
  unsigned m_Count;

 public:
  UniformBuffer(std::vector<T> const& data, GLenum usage = GL_DYNAMIC_DRAW);
  void write(std::vector<T> const& data, unsigned to = 0);
  void write(T const& data, unsigned to = 0);
  unsigned count() const;
  std::size_t size() const;
  void bindBase(GLuint index) const;
};

}  // namespace engine

}  // namespace orbitals

#include "uniform_buffer.inl"