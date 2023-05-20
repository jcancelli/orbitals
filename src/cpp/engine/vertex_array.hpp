#pragma once

#include <GLES3/gl3.h>

#include "vertex_buffer.hpp"

namespace orbitals {

namespace engine {

class VertexArray {
 private:
  GLuint m_Id;

 public:
  template <class... T>
  VertexArray(VertexBuffer<T> const*... vbos) {
    glCall(glGenVertexArrays(1, &m_Id));
    bind();

    GLuint index = 0;
    (
        [&] {
          GLsizei offset = 0;
          vbos->bind();
          for (VertexAttribute const& attribute : vbos->getVertexLayout().getAttributes()) {
            glCall(glEnableVertexAttribArray(index));
            glCall(glVertexAttribPointer(index, attribute.count, attribute.type,
                                         attribute.normalized, vbos->getVertexLayout().stride(),
                                         (void*)offset));
            glCall(glVertexAttribDivisor(index, attribute.divisor));
            offset += attribute.size();
            index++;
          }
          vbos->unbind();
        }(),
        ...);

    unbind();
  }
  ~VertexArray();
  void bind() const;
  void unbind() const;
};

}  // namespace engine

}  // namespace orbitals
