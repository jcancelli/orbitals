#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "input_events.hpp"
#include "mesh.hpp"
#include "uniform_buffer.hpp"
#include "viewport.hpp"

namespace orbitals {

namespace engine {

class Scene {
 protected:
  std::shared_ptr<Camera> m_Camera;
  std::vector<std::shared_ptr<Mesh>> m_Meshes;

 public:
  Scene(std::shared_ptr<Camera> camera);
  void draw(std::shared_ptr<const Viewport> viewport) const;
  virtual void update(double deltaTime);
  virtual void handleInputEvent(InputEvent const& event);
  std::shared_ptr<const Camera> getCamera() const;
};

}  // namespace engine

}  // namespace orbitals
