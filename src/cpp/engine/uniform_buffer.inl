#pragma once

#include <cassert>

#include "debug.hpp"
#include "uniform_buffer.hpp"

namespace orbitals {

namespace engine {

template <class T>
UniformBuffer<T>::UniformBuffer(std::vector<T> const& data, GLenum usage)
    : Buffer<T>::Buffer(GL_UNIFORM_BUFFER, data, usage) {
}

template <class T>
void UniformBuffer<T>::bindBase(GLuint index) const {
  glCall(glBindBufferBase(GL_UNIFORM_BUFFER, index, this->id()));
}

}  // namespace engine

}  // namespace orbitals