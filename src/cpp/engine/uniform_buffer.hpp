#pragma once

#include <GLES3/gl3.h>

#include <vector>

#include "buffer.hpp"

namespace orbitals {

namespace engine {

template <class T>
class UniformBuffer : public Buffer<T> {
 public:
  UniformBuffer(std::vector<T> const& data, GLenum usage = GL_DYNAMIC_DRAW);

  void bindBase(GLuint index) const;
};

}  // namespace engine

}  // namespace orbitals

#include "uniform_buffer.inl"