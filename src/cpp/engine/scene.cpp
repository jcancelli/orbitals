#include "scene.hpp"

namespace orbitals {

namespace engine {

Scene::Scene(std::shared_ptr<Camera> camera) : m_Camera(camera) {
}

void Scene::draw(std::shared_ptr<const Viewport> viewport) const {
  std::for_each(
      m_Meshes.cbegin(), m_Meshes.cend(),
      [this, viewport](std::shared_ptr<Mesh> const& mesh) { mesh->draw(m_Camera, viewport); });
}

void Scene::update(double deltaTime) {
}

void Scene::handleInput(std::vector<Inputs::Event> events, Keyboard const& keyboard,
                        Mouse const& mouse) {
}

std::shared_ptr<const Camera> Scene::getCamera() const {
  return m_Camera;
}

}  // namespace engine

}  // namespace orbitals
