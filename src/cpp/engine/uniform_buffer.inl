#pragma once

#include <cassert>

#include "debug.hpp"
#include "uniform_buffer.hpp"

namespace orbitals {

namespace engine {

template <class T>
UniformBuffer<T>::UniformBuffer(std::vector<T> const& data, GLenum usage)
    : Buffer::Buffer(GL_UNIFORM_BUFFER, data, usage), m_Data{data} {
}

template <class T>
void UniformBuffer<T>::write(std::vector<T> const& data, unsigned to) {
  assert(to + data.size() <= count());
  std::copy(data.cbegin(), data.cend(), m_Data.begin() + to);
  glCall(glBufferSubData(GL_UNIFORM_BUFFER, to * sizeof(T), data.size() * sizeof(T), data.data()));
  unbind();
}

template <class T>
void UniformBuffer<T>::write(T const& data, unsigned to) {
  assert(to < count());
  m_Data[to] = data;
  bind();
  glCall(glBufferSubData(GL_UNIFORM_BUFFER, to * sizeof(T), sizeof(T), &data));
  unbind();
}

template <class T>
T UniformBuffer<T>::read(unsigned from) const {
  assert(from < count());
  return T(m_Data[from]);
}

template <class T>
unsigned UniformBuffer<T>::count() const {
  return m_Data.size();
}

template <class T>
std::size_t UniformBuffer<T>::size() const {
  return count() * sizeof(T);
}

template <class T>
void UniformBuffer<T>::bindBase(GLuint index) const {
  glCall(glBindBufferBase(GL_UNIFORM_BUFFER, index, id()));
}

}  // namespace engine

}  // namespace orbitals