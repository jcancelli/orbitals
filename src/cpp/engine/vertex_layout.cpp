#include "VertexLayout.hpp"

#include <cassert>

#include "glDebug.hpp"

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
    addAttribute(attribute.count, attribute.type, attribute.normalized);
  }
}

void VertexLayout::addAttribute(GLint count, GLenum type, GLboolean normalized) {
  VertexAttribute element = {count, type, normalized};
  m_Elements.push_back(element);
  m_Stride += element.size();
}

std::vector<VertexAttribute> const& VertexLayout::getAttributes() const {
  return m_Elements;
}

GLsizei VertexLayout::stride() const {
  return m_Stride;
}

}  // namespace engine

}  // namespace orbitals