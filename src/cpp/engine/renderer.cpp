
#include "renderer.hpp"

#include "../util/fs.hpp"
#include "primitives/debug.hpp"

namespace orbitals {

namespace engine {

static const math::mat4 homogCoordsToTextureCoordsMatrix({
    0.5, 0, 0, 0,      //
    0, 0.5, 0, 0,      //
    0, 0, 0.5, 0,      //
    0.5, 0.5, 0.5, 1,  //
});                    //

Renderer::Renderer()
    : SHADOW_MAP_SIZE(1024),
      m_ShadowMapTexture(SHADOW_MAP_SIZE, SHADOW_MAP_SIZE, GL_DEPTH_COMPONENT,
                         GL_DEPTH_COMPONENT32F, GL_FLOAT),
      m_ShadowMapShader(util::read_string("shaders/shadow_map.vert"),
                        util::read_string("shaders/shadow_map.frag")) {
  m_ShadowMapFBO.setDepthAttachment(m_ShadowMapTexture);
  m_ShadowMapFBO.bind();
  glCall(glDrawBuffers(0, nullptr));
  glCall(glReadBuffer(GL_NONE));
  m_ShadowMapFBO.unbind();
  glCall(glEnable(GL_CULL_FACE));
  glCall(glCullFace(GL_BACK));
}

void Renderer::render(std::shared_ptr<const Camera> camera,
                      std::vector<std::shared_ptr<Mesh>> const& meshes,
                      DirectionalLight const& light) {
  shadowPass(meshes, light);
  renderPass(camera, meshes, light);
  //   textureTest.draw(m_ShadowMapTexture);
}

void Renderer::handleEvents(std::vector<Event> events) {
}

void Renderer::shadowPass(std::vector<std::shared_ptr<Mesh>> const& meshes,
                          DirectionalLight const& light) {
  m_ShadowMapFBO.bind();
  m_ShadowMapShader.bind();
  m_ShadowMapTexture.bind();
  m_ShadowMapFBO.checkIsComplete();
  glCall(glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE));
  glCall(glClear(GL_DEPTH_BUFFER_BIT));
  m_ShadowMapShader.setUniformMat4("uLightSpaceMatrix", light.getCamera().getCameraMatrix());
  for (auto const& mesh : meshes) {
    mesh->bind();
    if (mesh->isInstanced()) {
      glCall(glDrawElementsInstanced(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_INT, 0,
                                     mesh->getInstanceCount()));
    } else {
      glCall(glDrawElements(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_INT, 0));
    }
    mesh->unbind();
  }
  m_ShadowMapTexture.unbind();
  m_ShadowMapShader.unbind();
  m_ShadowMapFBO.unbind();
}

void Renderer::renderPass(std::shared_ptr<const Camera> camera,
                          std::vector<std::shared_ptr<Mesh>> const& meshes,
                          DirectionalLight const& light) {
  Viewport& viewport = Viewport::getInstance();
  glCall(glViewport(0, 0, viewport.getWidth(), viewport.getHeight()));
  glCall(glClearColor(1, 1, 1, 1));
  glCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
  for (auto const& mesh : meshes) {
    auto material = mesh->getMaterial();
    auto& shader = material->getShader();
    material->bind();
    mesh->bind();
    shader.setUniformMat4("uViewProjMatrix", camera->getCameraMatrix());
    // shader.setUniformMat4("uLightSpaceMatrix",
    //                       //   homogCoordsToTextureCoordsMatrix *
    //                       OrthograficCamera(0, 1, 0, -25, 25, -25, 25).getCameraMatrix());
    shader.setUniformMat4("uLightSpaceMatrix",
                          homogCoordsToTextureCoordsMatrix * light.getCamera().getCameraMatrix());
    shader.setUniform3f("uViewPosition", camera->getPosition());
    m_ShadowMapTexture.bind();
    m_ShadowMapTexture.setActive(GL_TEXTURE0);
    shader.setUniform1i("uShadowMap", 0);
    shader.setUniform3f("uLightColor", light.getColor());
    shader.setUniform3f("uLightDirection", light.getInvertedDirection());
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
