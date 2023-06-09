#pragma once

#include <memory>

#include "io/viewport.hpp"
#include "primitives/index_buffer.hpp"
#include "primitives/shader.hpp"
#include "primitives/texture.hpp"
#include "primitives/vertex_array.hpp"
#include "primitives/vertex_buffer.hpp"
#include "primitives/vertex_layout.hpp"

namespace orbitals {

namespace engine {

class Texture2DTest {
 private:
  struct SimpleVertex {
    inline static const VertexLayout layout{{2, GL_FLOAT, GL_FALSE}, {2, GL_FLOAT, GL_FALSE}};
    float x, y;
    float u, v;
  };

 private:
  VertexBuffer<SimpleVertex> m_VBO;
  IndexBuffer m_IBO;
  VertexArray m_VAO;
  Shader m_Shader;
  Viewport& m_Viewport;

 public:
  Texture2DTest();
  void draw(Texture2D& texture);
};

}  // namespace engine

}  // namespace orbitals
