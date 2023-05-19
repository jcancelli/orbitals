#pragma once

#include "buffer.hpp"
#include "debug.hpp"

namespace orbitals {

namespace engine {

template <class T>
Buffer<T>::~Buffer() {
  glCall(glDeleteBuffers(1, &m_Id));
}

template <class T>
void Buffer<T>::bind() const {
  glCall(glBindBuffer(m_Target, m_Id));
}

template <class T>
void Buffer<T>::unbind() const {
  glCall(glBindBuffer(m_Target, 0));
}

template <class T>
void Buffer<T>::write(std::vector<T> const& data, unsigned to) {
  assert(to + data.size() <= count());
  std::copy(data.cbegin(), data.cend(), m_Data.begin() + to);
  bind();
  glCall(glBufferSubData(GL_UNIFORM_BUFFER, to * sizeof(T), data.size() * sizeof(T), data.data()));
  unbind();
}

template <class T>
void Buffer<T>::write(T const& data, unsigned to) {
  assert(to < count());
  m_Data[to] = data;
  bind();
  glCall(glBufferSubData(GL_UNIFORM_BUFFER, to * sizeof(T), sizeof(T), &data));
  unbind();
}

template <class T>
T Buffer<T>::read(unsigned from) const {
  assert(from < count());
  return T(m_Data[from]);
}

template <class T>
GLuint Buffer<T>::id() const {
  return m_Id;
}

template <class T>
GLenum Buffer<T>::target() const {
  return m_Target;
}

template <class T>
GLsizei Buffer<T>::size() const {
  return count() * sizeof(T);
}

template <class T>
std::size_t Buffer<T>::count() const {
  return m_Data.size();
}

}  // namespace engine

}  // namespace orbitals