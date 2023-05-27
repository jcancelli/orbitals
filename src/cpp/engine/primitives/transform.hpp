#pragma once

#include "../../math/matrix.hpp"
#include "../../math/quaternion.hpp"
#include "../../math/vector.hpp"
#include "vertex_layout.hpp"

namespace orbitals {

namespace engine {

class Transform {
 public:
  static const VertexLayout layout;

 private:
  math::vec3 m_Translation;
  math::quatf m_Rotation;
  math::vec3 m_Scale;
  math::mat4 m_Matrix;

 public:
  Transform();
  Transform& setTranslation(float x, float y, float z);
  Transform& setTranslation(math::vec3 const& translation);
  Transform& translate(float x, float y, float z);
  Transform& translate(math::vec3 const& translation);
  math::vec3 getTranslation() const;
  Transform& setRotation(float angle, math::vec3 const& axis);
  Transform& setRotation(math::quatf const& rotation);
  Transform& setRotation(float x, float y, float z);
  Transform& rotate(float angle, math::vec3 const& axis);
  Transform& rotate(math::quatf const& rotation);
  Transform& rotate(float x, float y, float z);
  math::quatf getRotation() const;
  Transform& setScale(float x, float y, float z);
  Transform& setScale(math::vec3 const& scale);
  Transform& scale(float x, float y, float z);
  Transform& scale(math::vec3 const& scale);
  math::vec3 getScale() const;
  math::mat4 matrix() const;

 private:
  void updateMatrix();
};

}  // namespace engine

}  // namespace orbitals
