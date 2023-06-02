#include "texture_test.hpp"

#include "../util/fs.hpp"

namespace orbitals {

namespace engine {

Texture2DTest::Texture2DTest(std::shared_ptr<Viewport> viewport)
    : m_VBO({SimpleVertex{-1, 1, 0, 1}, SimpleVertex{-1, -1, 0, 0}, SimpleVertex{1, 1, 1, 1},
             SimpleVertex{1, -1, 1, 0}}),
      m_IBO({0, 2, 1, 2, 1, 3}),
      m_VAO(&m_VBO),
      m_Shader(util::read_string("shaders/debug_texture.vert"),
               util::read_string("shaders/debug_texture.frag")),
      m_Viewport(viewport) {
}

void Texture2DTest::draw(Texture2D& texture) {
  m_VAO.bind();
  m_IBO.bind();
  m_Shader.bind();
  texture.bind();
  glCall(glViewport(0, 0, m_Viewport->getWidth(), m_Viewport->getHeight()));
  glCall(glClearColor(1, 1, 1, 1));
  glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  texture.setActive(GL_TEXTURE0);
  m_Shader.setUniform1i("uTexture", 0);
  glCall(glDrawElements(GL_TRIANGLES, m_IBO.count(), GL_UNSIGNED_INT, 0));
}

}  // namespace engine

}  // namespace orbitals
