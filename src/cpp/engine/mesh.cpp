#include "mesh.hpp"

#include <iostream>

#include "../math/projection_matrix.hpp"
#include "../math/trigonometry.hpp"

namespace orbitals {

namespace engine {

void Mesh::bind() const {
  m_VAO.bind();
  m_IBO.bind();
}

void Mesh::unbind() const {
  m_VAO.unbind();
  m_IBO.unbind();
}

unsigned Mesh::getInstanceCount() const {
  return m_InstancesCount;
}

unsigned Mesh::getVerticesCount() const {
  return m_IBO.count();
}

bool Mesh::isInstanced() const {
  return m_InstancesCount > 1;
}

void Mesh::setMaterial(std::shared_ptr<Material> material) {
  m_Material = material;
}

std::shared_ptr<Material> Mesh::getMaterial() const {
  return m_Material;
}

void Mesh::setTransform(Transform const& transform, std::size_t index) {
  assert(index < m_InstancesCount);
  m_TransformsVBO.write(transform, index);
}

void Mesh::setTransforms(std::vector<Transform> const& transforms, std::size_t index) {
  assert(transforms.size() + index <= m_TransformsVBO.count());
  m_TransformsVBO.write(transforms, index);
}

Transform Mesh::getTransform(std::size_t index) const {
  assert(index < m_InstancesCount);
  return m_TransformsVBO.read(index);
}

}  // namespace engine

}  // namespace orbitals
