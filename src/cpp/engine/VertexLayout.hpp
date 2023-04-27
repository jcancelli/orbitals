#pragma once

#include <GLES3/gl3.h>

#include <vector>

namespace orbitals {

namespace engine {

struct VertexAttribute {
  GLint count;
  GLenum type;
  GLboolean normalized = GL_FALSE;

  GLsizei size() const;
};

class VertexLayout {
 private:
  std::vector<VertexAttribute> m_Elements;
  GLuint m_Stride;

 public:
  VertexLayout();
  VertexLayout(std::initializer_list<VertexAttribute> attributes);
  void addAttribute(GLint count, GLenum type, GLboolean normalized);
  std::vector<VertexAttribute> const& getAttributes() const;
  GLsizei stride() const;
};

}  // namespace engine

}  // namespace orbitals
