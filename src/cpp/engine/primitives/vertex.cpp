#include "vertex.hpp"

namespace orbitals {

namespace engine {

const VertexLayout Vertex::layout{{3, GL_FLOAT, GL_FALSE}, {3, GL_FLOAT, GL_FALSE}};

Vertex::Vertex() : position(0, 0, 0), normal(0, 0, 0) {
}

Vertex::Vertex(Vertex const& other) : position(other.position), normal(other.normal) {
}

Vertex::Vertex(float x, float y, float z) : position(x, y, z), normal(x, y, z) {
}

Vertex::Vertex(float x, float y, float z, float normX, float normY, float normZ)
    : position(x, y, z), normal(normX, normY, normZ) {
}

Vertex::Vertex(math::vec3 const& position) : position(position), normal(position) {
}

Vertex::Vertex(math::vec3 const& position, math::vec3 const& normal)
    : position(position), normal(normal) {
}

}  // namespace engine

}  // namespace orbitals
