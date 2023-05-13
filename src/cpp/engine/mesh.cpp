#include "mesh.hpp"

#include <iostream>

#include "../math/projection_matrix.hpp"
#include "../math/trigonometry.hpp"

#define FOV float(math::radians(80))
#define Z_NEAR 0.1f
#define Z_FAR 2000.f

namespace orbitals {

namespace engine {

void Mesh::draw(Camera const& camera, std::shared_ptr<Viewport> const viewport) const {
  m_Material->bind();
  m_VAO.bind();
  m_VBO.bind();
  m_IBO.bind();
  m_ModelMatricesUBO.bindBase(0);
  m_Material->getShader().bindUniformBlock("ModelMatrices", 0);
  math::mat4 projMatrix(math::perspective(FOV, viewport->aspectRatio(), Z_NEAR, Z_FAR));
  m_Material->getShader().setUniformMat4("viewProjMatrix", projMatrix * camera.viewMatrix());
  if (m_InstancesCount > 1) {
    glCall(glDrawElementsInstanced(GL_TRIANGLES, m_IBO.getCount(), GL_UNSIGNED_INT, 0,
                                   m_InstancesCount));
  } else {
    glCall(glDrawElements(GL_TRIANGLES, m_IBO.getCount(), GL_UNSIGNED_INT, 0));
  }
  m_Material->unbind();
  m_VAO.unbind();
  m_VBO.unbind();
  m_IBO.unbind();
  m_ModelMatricesUBO.unbind();
}

void Mesh::setMaterial(std::shared_ptr<Material> material) {
  m_Material = material;
}

std::shared_ptr<Material> const Mesh::getMaterial() const {
  return m_Material;
}

void Mesh::setModelMatrix(math::mat4 const& matrix, std::size_t index) {
  assert(index < m_InstancesCount);
  m_ModelMatricesUBO.write(matrix, index);
}

void Mesh::setModelMatrices(std::vector<math::mat4> matrices, std::size_t index) {
  assert(matrices.size() + index <= m_ModelMatricesUBO.count());
  m_ModelMatricesUBO.write(matrices, index);
}

math::mat4 Mesh::getModelMatrix(std::size_t index) const {
  assert(index < m_InstancesCount);
  return m_ModelMatricesUBO.read(index);
}

}  // namespace engine

}  // namespace orbitals