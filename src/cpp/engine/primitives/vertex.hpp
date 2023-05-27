#pragma once

#include "../../math/vector.hpp"
#include "vertex_layout.hpp"

namespace orbitals {

namespace engine {

struct Vertex {
  static const VertexLayout layout;
  math::vec3 position;
  math::vec3 normal;

  Vertex();
  Vertex(Vertex const& other);
  Vertex(float x, float y, float z);
  Vertex(float x, float y, float z, float normX, float normY, float normZ);
  Vertex(math::vec3 const& position);
  Vertex(math::vec3 const& position, math::vec3 const& normal);
};

}  // namespace engine

}  // namespace orbitals
