#pragma once

#include <ostream>

#include "../math/vector.hpp"
#include "VertexBufferLayout.hpp"

namespace orbitals {

namespace engine {

class Vertex {
 private:
  static VertexBufferLayout s_VertexLayout;

 public:
  const float x, y, z;
  const float normX, normY, normZ;

 public:
  Vertex(math::vec3 const& position, math::vec3 const& normal);
  Vertex(float x, float y, float z, float normX, float normY, float normZ);
  VertexBufferLayout const& getVertexLayout() const;
};

inline std::ostream& operator<<(std::ostream& os, Vertex const& vertex);

}  // namespace engine

}  // namespace orbitals
