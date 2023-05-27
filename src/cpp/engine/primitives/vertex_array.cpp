#include "vertex_array.hpp"

#include "debug.hpp"

namespace orbitals {

namespace engine {

VertexArray::~VertexArray() {
  glCall(glDeleteVertexArrays(1, &m_Id));
}

void VertexArray::bind() const {
  glCall(glBindVertexArray(m_Id));
}

void VertexArray::unbind() const {
  glCall(glBindVertexArray(0));
}

}  // namespace engine

}  // namespace orbitals