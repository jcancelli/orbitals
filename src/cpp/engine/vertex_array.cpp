#include "vertex_array.hpp"

#include "debug.hpp"

namespace orbitals {

namespace engine {

VertexArray::VertexArray(VertexBuffer const& vbo) {
  glCall(glGenVertexArrays(1, &m_Id));
  bind();
  vbo.bind();
  auto const& attributes = vbo.getVertexLayout().getAttributes();
  int offset = 0;
  for (int i = 0; i < attributes.size(); i++) {
    auto const& attribute = attributes[i];
    glCall(glEnableVertexAttribArray(i));
    glCall(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized,
                                 vbo.getVertexLayout().stride(), (void*)offset));
    offset += attribute.size();
  }
  unbind();
  vbo.unbind();
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