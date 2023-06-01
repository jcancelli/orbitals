
#include "renderer.hpp"

#include "../util/fs.hpp"
#include "primitives/debug.hpp"

namespace orbitals {

namespace engine {

Renderer::Renderer(std::shared_ptr<Viewport> viewport)
    : SHADOW_MAP_SIZE(1024),
      m_Viewport(viewport),
      m_ShadowMapTexture(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, GL_DEPTH_COMPONENT,
                         GL_DEPTH_COMPONENT32F, GL_FLOAT),
      m_ShadowMapShader(util::read_string("shaders/shadow_map.vert"),
                        util::read_string("shaders/shadow_map.frag")) {
  m_ShadowMapFBO.setDepthAttachment(m_ShadowMapTexture);
  m_ShadowMapFBO.bind();
  GLenum drawBuffer[1] = {GL_NONE};
  glCall(glDrawBuffers(1, drawBuffer));
  m_ShadowMapFBO.unbind();
}

void Renderer::render(std::shared_ptr<const Camera> camera,
                      std::vector<std::shared_ptr<Mesh>> const& meshes,
                      DirectionalLight const& light) {
  shadowPass(meshes, light);
  renderPass(camera, meshes, light);
}

void Renderer::setViewport(std::shared_ptr<Viewport> viewport) {
  m_Viewport = viewport;
}

std::shared_ptr<Viewport> Renderer::getViewport() const {
  return m_Viewport;
}

void Renderer::shadowPass(std::vector<std::shared_ptr<Mesh>> const& meshes,
                          DirectionalLight const& light) {
  m_ShadowMapFBO.checkIsComplete();
  m_ShadowMapFBO.bind();
  m_ShadowMapShader.bind();
  glCall(glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE));
  m_ShadowMapShader.setUniformMat4(
      "uLightViewProjMatrix",
      math::orthogonal<float>(-25, 25, -25, 25, .1f, 2000.f) *
          Camera(light.getInvertedDirection()).lookAt(0, 0, 0).viewMatrix());
  for (auto const& mesh : meshes) {
    auto& shader = mesh->getMaterial()->getShader();
    mesh->bind();
    if (mesh->isInstanced()) {
      glCall(glDrawElementsInstanced(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_INT, 0,
                                     mesh->getInstanceCount()));
    } else {
      glCall(glDrawElements(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_INT, 0));
    }
    mesh->unbind();
  }
  m_ShadowMapFBO.unbind();
  m_ShadowMapShader.unbind();
}

void Renderer::renderPass(std::shared_ptr<const Camera> camera,
                          std::vector<std::shared_ptr<Mesh>> const& meshes,
                          DirectionalLight const& light) {
  glCall(glViewport(0, 0, m_Viewport->getWidth(), m_Viewport->getHeight()));
  for (auto const& mesh : meshes) {
    auto material = mesh->getMaterial();
    auto& shader = material->getShader();
    material->bind();
    mesh->bind();
    shader.setUniformMat4(                                                                  //
        "uProjectionMatrix",                                                                //
        math::perspective(camera->getFOV(), m_Viewport->aspectRatio(), camera->getZNear(),  //
                          camera->getZFar())                                                //
    );                                                                                      //
    shader.setUniformMat4("uViewMatrix", camera->viewMatrix());
    shader.setUniform3f("uViewPosition", camera->getPosition());
    if (mesh->isInstanced()) {
      glCall(glDrawElementsInstanced(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_INT, 0,
                                     mesh->getInstanceCount()));
    } else {
      glCall(glDrawElements(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_INT, 0));
    }
    material->unbind();
    mesh->unbind();
  }
}

}  // namespace engine

}  // namespace orbitals
