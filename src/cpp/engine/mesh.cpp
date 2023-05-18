#include "mesh.hpp"

#include <iostream>

#include "../math/projection_matrix.hpp"
#include "../math/trigonometry.hpp"

namespace orbitals {

namespace engine {

static const float FOV = math::radians(72);
static const float Z_NEAR = 0.1f;
static const float Z_FAR = 2000.f;

void Mesh::draw(std::shared_ptr<const Camera> camera,
                std::shared_ptr<const Viewport> viewport) const {
  m_Material->bind();
  m_VAO.bind();
  m_VBO.bind();
  m_IBO.bind();
  m_ModelTransformsUBO.bindBase(0);
  m_Material->getShader().bindUniformBlock("TransformsBuffer", 0);
  m_Material->getShader().setUniformMat4(                             //
      "uProjectionMatrix",                                            //
      math::perspective(FOV, viewport->aspectRatio(), Z_NEAR, Z_FAR)  //
  );                                                                  //
  m_Material->getShader().setUniformMat4("uViewMatrix", camera->viewMatrix());
  m_Material->getShader().setUniform3f("uViewPosition", camera->getPosition());
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
  m_ModelTransformsUBO.unbind();
}

void Mesh::setMaterial(std::shared_ptr<Material> material) {
  m_Material = material;
}

std::shared_ptr<const Material> Mesh::getMaterial() const {
  return m_Material;
}

void Mesh::setTransform(Transform const& transform, std::size_t index) {
  assert(index < m_InstancesCount);
  m_ModelTransformsUBO.write(transform, index);
}

void Mesh::setTransforms(std::vector<Transform> const& transforms, std::size_t index) {
  assert(transforms.size() + index <= m_ModelTransformsUBO.count());
  m_ModelTransformsUBO.write(transforms, index);
}

Transform Mesh::getTransform(std::size_t index) const {
  assert(index < m_InstancesCount);
  return m_ModelTransformsUBO.read(index);
}

}  // namespace engine

}  // namespace orbitals
