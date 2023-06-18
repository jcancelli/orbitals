#pragma once

#include <memory>
#include <vector>

#include "event.hpp"
#include "io/viewport.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "primitives/frame_buffer.hpp"
#include "primitives/shader.hpp"
#include "primitives/texture.hpp"
#include "texture_test.hpp"

namespace orbitals {

namespace engine {

class Renderer {
 private:
  const GLsizei SHADOW_MAP_SIZE;
  FrameBuffer m_ShadowMapFBO;
  Texture2D m_ShadowMapTexture;
  Shader m_ShadowMapShader;
  Texture2DTest textureTest;

 public:
  Renderer();
  void render(std::shared_ptr<const Camera> camera,
              std::vector<std::shared_ptr<Mesh>> const& meshes, DirectionalLight const& light);
  void handleEvents(std::vector<Event> events);

 private:
  void shadowPass(std::vector<std::shared_ptr<Mesh>> const& meshes, DirectionalLight const& light);
  void renderPass(std::shared_ptr<const Camera> camera,
                  std::vector<std::shared_ptr<Mesh>> const& meshes, DirectionalLight const& light);
};

}  // namespace engine

}  // namespace orbitals
