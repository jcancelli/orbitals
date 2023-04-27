#include "Vertex.hpp"

namespace orbitals {

namespace engine {

Vertex::Vertex(float x, float y, float z, float normX, float normY, float normZ)
    : x{x}, y{y}, z{z}, normX{normX}, normY{normY}, normZ{normZ} {
  s_VertexLayout.addAttribute(3, GL_FLOAT, GL_FALSE);
  s_VertexLayout.addAttribute(3, GL_FLOAT, GL_FALSE);
}

Vertex::Vertex(math::vec3 const& position, math::vec3 const& normal)
    : x{position.x()},
      y{position.y()},
      z{position.z()},
      normX{normal.x()},
      normY{normal.y()},
      normZ{normal.z()} {
  s_VertexLayout.addAttribute(3, GL_FLOAT, GL_FALSE);
  s_VertexLayout.addAttribute(3, GL_FLOAT, GL_FALSE);
}

VertexBufferLayout const& Vertex::getLayout() {
  return s_VertexLayout;
}

inline std::ostream& operator<<(std::ostream& os, Vertex const& vertex) {
  return os << "Pos: {" << vertex.x << ", " << vertex.y << ", " << vertex.z << "} Norm: {"
            << vertex.normX << ", " << vertex.normY << ", " << vertex.normZ << "}";
}

}  // namespace engine

}  // namespace orbitals
