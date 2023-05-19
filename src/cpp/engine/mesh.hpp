#pragma once

#include <GLES3/gl3.h>

#include <algorithm>
#include <cassert>
#include <memory>

#include "../math/matrix.hpp"
#include "../math/projection_matrix.hpp"
#include "../math/trigonometry.hpp"
#include "../util/fetch.hpp"
#include "camera.hpp"
#include "debug.hpp"
#include "index_buffer.hpp"
#include "material.hpp"
#include "transform.hpp"
#include "uniform_buffer.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "viewport.hpp"

namespace orbitals {

namespace engine {

class Mesh {
 protected:
  VertexBuffer m_VBO;
  IndexBuffer m_IBO;
  VertexArray m_VAO;
  unsigned m_InstancesCount;
  std::shared_ptr<Material> m_Material;
  UniformBuffer<Transform> m_ModelTransformsUBO;

 public:
  template <class TVertex>
  Mesh(std::vector<TVertex> const& vertices, std::vector<GLuint> const& indices,
       std::shared_ptr<Material> material, unsigned instancesCount = 1)
      : m_VBO(vertices),
        m_IBO(indices),
        m_VAO{&m_VBO},
        m_InstancesCount{instancesCount},
        m_Material(material),
        m_ModelTransformsUBO(std::vector<Transform>(instancesCount, Transform())) {
    assert(instancesCount > 0);
  }
  void draw(std::shared_ptr<const Camera> camera, std::shared_ptr<const Viewport> viewport) const;
  void setMaterial(std::shared_ptr<Material> material);
  std::shared_ptr<const Material> getMaterial() const;
  void setTransform(Transform const& transform, std::size_t index = 0);
  void setTransforms(std::vector<Transform> const& transforms, std::size_t index = 0);
  Transform getTransform(std::size_t index = 0) const;
};

}  // namespace engine

}  // namespace orbitals
