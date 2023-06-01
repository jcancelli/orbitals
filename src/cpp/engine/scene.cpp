#include "scene.hpp"

namespace orbitals {

namespace engine {

Scene::Scene(std::shared_ptr<Camera> camera) : m_Camera(camera) {
}

void Scene::draw(std::shared_ptr<Renderer> renderer) const {
  renderer->render(m_Camera, m_Meshes, m_Light);
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
