#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "inputs.hpp"
#include "keyboard.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "renderer.hpp"

namespace orbitals {

namespace engine {

class Scene {
 protected:
  std::shared_ptr<Camera> m_Camera;
  std::vector<std::shared_ptr<Mesh>> m_Meshes;
  DirectionalLight m_Light;

 public:
  Scene();
  void draw(std::shared_ptr<Renderer> renderer) const;
  virtual void update(double deltaTime);
  virtual void handleInput(std::vector<Inputs::Event> events, Keyboard const& keyboard,
                           Mouse const& mouse);
  void setCamera(std::shared_ptr<Camera> camera);
  std::shared_ptr<Camera> getCamera() const;
};

}  // namespace engine

}  // namespace orbitals
