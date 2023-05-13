#include "scene.hpp"

namespace orbitals {

namespace engine {

void Scene::draw(std::shared_ptr<Viewport> const& viewport) const {
  std::for_each(
      m_Meshes.cbegin(), m_Meshes.cend(),
      [this, viewport](std::shared_ptr<Mesh> const& mesh) { mesh->draw(m_Camera, viewport); });
}

void Scene::update(double deltaTime) {
}

void Scene::handleInputEvent(InputEvent const& event) {
}

Camera const& Scene::getCamera() const {
  return m_Camera;
}

}  // namespace engine

}  // namespace orbitals
