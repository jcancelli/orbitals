#include "VertexArray.hpp"

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

VertexArray::VertexArray(VertexBuffer const& vbo, VertexBufferLayout const& layout) {
  glCall(glGenVertexArrays(1, &m_Id));
  bind();
  const auto const& attributes = layout.getAttributes();
  int offset = 0;
  for (int i = 0; i < attributes.size(); i++) {
    const auto const& attribute = attributes[i];
    glCall(glEnableVertexAttribArray(i));
    glCall(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized,
                                 layout.stride(), (void*)offset));
    offset += attribute.size();
  }
}

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