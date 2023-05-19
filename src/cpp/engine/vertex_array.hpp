#pragma once

#include <GLES3/gl3.h>

#include "vertex_buffer.hpp"

namespace orbitals {

namespace engine {

class VertexArray {
 private:
  GLuint m_Id;

 public:
  template <class T>
  VertexArray(std::initializer_list<GenericVertexBuffer<T> const*> vbos) {
    glCall(glGenVertexArrays(1, &m_Id));
    bind();
    for (auto const* vbo : vbos) {
      vbo->bind();
      auto const& attributes = vbo->getVertexLayout().getAttributes();
      int offset = 0;
      for (int i = 0; i < attributes.size(); i++) {
        auto const& attribute = attributes[i];
        glCall(glEnableVertexAttribArray(i));
        glCall(glVertexAttribPointer(i, attribute.count, attribute.type, attribute.normalized,
                                     vbo->getVertexLayout().stride(), (void*)offset));
        offset += attribute.size();
      }
      vbo->unbind();
    }
    unbind();
  }
  ~VertexArray();
  void bind() const;
  void unbind() const;
};

}  // namespace engine

}  // namespace orbitals
