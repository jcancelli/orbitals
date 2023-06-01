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
#include "material.hpp"
#include "primitives/debug.hpp"
#include "primitives/index_buffer.hpp"
#include "primitives/transform.hpp"
#include "primitives/uniform_buffer.hpp"
#include "primitives/vertex_array.hpp"
#include "primitives/vertex_buffer.hpp"
#include "viewport.hpp"

namespace orbitals {

namespace engine {

class Mesh {
 protected:
  VertexDataBuffer m_GeometryVBO;
  VertexTransformsBuffer m_TransformsVBO;
  IndexBuffer m_IBO;
  VertexArray m_VAO;
  unsigned m_InstancesCount;
  std::shared_ptr<Material> m_Material;

 public:
  template <class TVertex>
  Mesh(std::vector<TVertex> const& vertices, std::vector<GLuint> const& indices,
       std::shared_ptr<Material> material, unsigned instancesCount = 1)
      : m_GeometryVBO(vertices),
        m_TransformsVBO(std::vector(instancesCount, Transform()), GL_DYNAMIC_DRAW),
        m_IBO(indices),
        m_VAO(&m_GeometryVBO, &m_TransformsVBO),
        m_InstancesCount{instancesCount},
        m_Material(material) {
    assert(instancesCount > 0);
  }
  void bind() const;
  void unbind() const;
  unsigned getInstanceCount() const;
  unsigned getVerticesCount() const;
  bool isInstanced() const;
  void setMaterial(std::shared_ptr<Material> material);
  std::shared_ptr<Material> getMaterial() const;
  void setTransform(Transform const& transform, std::size_t index = 0);
  void setTransforms(std::vector<Transform> const& transforms, std::size_t index = 0);
  Transform getTransform(std::size_t index = 0) const;
};

}  // namespace engine

}  // namespace orbitals
