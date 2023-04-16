#include "VertexBufferLayout.hpp"

#include <cassert>

#include "glDebug.hpp"

namespace orbitals {

namespace engine {

GLsizei VertexBufferLayoutElement::size() const {
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

VertexBufferLayout::VertexBufferLayout() : m_Stride{0} {
}

void VertexBufferLayout::addAttribute(GLint count, GLenum type, GLboolean normalized) {
  VertexBufferLayoutElement element = {count, type, normalized};
  m_Elements.push_back(element);
  m_Stride += element.size();
}

std::vector<VertexBufferLayoutElement> const& VertexBufferLayout::getAttributes() const {
  return m_Elements;
}

GLsizei VertexBufferLayout::stride() const {
  return m_Stride;
}

}  // namespace engine

}  // namespace orbitals