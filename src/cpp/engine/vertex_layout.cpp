#include "vertex_layout.hpp"

#include <cassert>

#include "debug.hpp"

namespace orbitals {

namespace engine {

GLsizei VertexAttribute::size() const {
  switch (type) {
    case GL_FLOAT:
      return sizeof(GLfloat) * count;
    case GL_INT:
      return sizeof(GLint) * count;
    case GL_UNSIGNED_INT:
      return sizeof(GLuint) * count;
    default:
      assert(false);
  }
}

VertexLayout::VertexLayout() {
}

VertexLayout::VertexLayout(std::initializer_list<VertexAttribute> attributes) {
  for (auto const& attribute : attributes) {
    addAttribute(attribute);
  }
}

void VertexLayout::addAttribute(VertexAttribute const& attribute) {
  m_Elements.push_back(attribute);
  m_Stride += attribute.size();
}

std::vector<VertexAttribute> const& VertexLayout::getAttributes() const {
  return m_Elements;
}

GLsizei VertexLayout::stride() const {
  return m_Stride;
}

}  // namespace engine

}  // namespace orbitals