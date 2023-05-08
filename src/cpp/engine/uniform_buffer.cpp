#include "uniform_buffer.hpp"

#include <cassert>

#include "debug.hpp"

namespace orbitals {

namespace engine {

template <class T>
UniformBuffer<T>::UniformBuffer(std::vector<T> const& data, GLenum usage)
    : Buffer::Buffer(GL_UNIFORM_BUFFER, data, usage), m_Count{data.size()} {
}

template <class T>
void UniformBuffer<T>::write(std::vector<T> const& data, unsigned to) {
  assert(to + data.size() <= m_Count);
  bind();
  glCall(glBufferSubData(GL_UNIFORM_BUFFER, to * sizeof(T), data.size() * sizeof(T), data.data()));
  unbind();
}

template <class T>
void UniformBuffer<T>::write(T const& data, unsigned to) {
  assert(to < m_Count);
  bind();
  glCall(glBufferSubData(GL_UNIFORM_BUFFER, to * sizeof(T), sizeof(T), &data));
  unbind();
}

template <class T>
unsigned UniformBuffer<T>::count() const {
  return m_Count;
}

template <class T>
std::size_t UniformBuffer<T>::size() const {
  return m_Count * sizeof(T);
}

template <class T>
GLuint UniformBuffer<T>::bindBase(GLuint index) const {
  glCall(return glBindBufferBase(GL_UNIFORM_BUFFER, index, id()));
}

}  // namespace engine

}  // namespace orbitals