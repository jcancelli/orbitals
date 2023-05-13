#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "camera.hpp"
#include "mesh.hpp"
#include "uniform_buffer.hpp"
#include "viewport.hpp"

namespace orbitals {

namespace engine {

class Scene {
 protected:
  Camera m_Camera;
  std::vector<std::shared_ptr<Mesh>> m_Meshes;

 public:
  void draw(std::shared_ptr<Viewport> const& viewport) const;
  virtual void update(double deltaTime);
  Camera const& getCamera() const;
};

}  // namespace engine

}  // namespace orbitals
