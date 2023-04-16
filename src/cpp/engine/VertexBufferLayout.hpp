#pragma once

#include <GLES3/gl3.h>

#include <vector>

namespace orbitals {

namespace engine {

struct VertexBufferLayoutElement {
  GLint count;
  GLenum type;
  GLboolean normalized;

  GLsizei size() const;
};

class VertexBufferLayout {
 private:
  std::vector<VertexBufferLayoutElement> m_Elements;
  GLuint m_Stride;

 public:
  VertexBufferLayout();
  void addAttribute(GLint count, GLenum type, GLboolean normalized);
  std::vector<VertexBufferLayoutElement> const& getAttributes() const;
  GLsizei stride() const;
};

}  // namespace engine

}  // namespace orbitals
