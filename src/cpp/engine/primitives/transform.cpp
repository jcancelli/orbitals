#include "transform.hpp"

namespace orbitals {

namespace engine {

const VertexLayout Transform::layout{
    // trasaltion
    {3, GL_FLOAT, GL_FALSE, 1},
    // rotation
    {4, GL_FLOAT, GL_FALSE, 1},
    // scale
    {3, GL_FLOAT, GL_FALSE, 1},
    // model matrix
    {4, GL_FLOAT, GL_FALSE, 1},
    {4, GL_FLOAT, GL_FALSE, 1},
    {4, GL_FLOAT, GL_FALSE, 1},
    {4, GL_FLOAT, GL_FALSE, 1},
};

Transform::Transform()
    : m_Translation(0, 0, 0),
      m_Rotation(0, math::vec3(1, 0, 0)),
      m_Scale(1, 1, 1),
      m_Matrix(math::mat4(1)) {
}

Transform& Transform::setTranslation(float x, float y, float z) {
  return setTranslation(math::vec3(x, y, z));
}

Transform& Transform::setTranslation(math::vec3 const& translation) {
  const math::vec3 diff = translation - m_Translation;
  m_Translation = translation;
  m_Matrix.translate(diff);
  return *this;
}

Transform& Transform::translate(float x, float y, float z) {
  return translate(math::vec3(x, y, z));
}

Transform& Transform::translate(math::vec3 const& translation) {
  m_Translation += translation;
  m_Matrix.translate(translation);
  return *this;
}

math::vec3 Transform::getTranslation() const {
  return m_Translation;
}

Transform& Transform::setRotation(float angle, math::vec3 const& axis) {
  m_Rotation = math::quatf(angle, axis);
  updateMatrix();
  return *this;
}

Transform& Transform::setRotation(math::quatf const& rotation) {
  m_Rotation = rotation;
  updateMatrix();
  return *this;
}

Transform& Transform::setRotation(float x, float y, float z) {
  m_Rotation = math::quatf(math::vec3(x, y, z));
  updateMatrix();
  return *this;
}

Transform& Transform::rotate(float angle, math::vec3 const& axis) {
  m_Rotation = math::quatf(angle, axis) * m_Rotation;
  m_Matrix.rotate(angle, axis);
  return *this;
}

Transform& Transform::rotate(math::quatf const& rotation) {
  m_Rotation = rotation * m_Rotation;
  m_Matrix.rotate(rotation);
  return *this;
}

Transform& Transform::rotate(float x, float y, float z) {
  const math::quatf rotation(math::vec3(x, y, z));
  m_Rotation = rotation * m_Rotation;
  m_Matrix.rotate(rotation);
  return *this;
}

math::quatf Transform::getRotation() const {
  return m_Rotation;
}

Transform& Transform::setScale(float x, float y, float z) {
  assert(x >= 0 && y >= 0 && z >= 0);
  return setScale(math::vec3(x, y, z));
}

Transform& Transform::setScale(math::vec3 const& scale) {
  assert(scale.x() >= 0 && scale.y() >= 0 && scale.z() >= 0);
  const math::vec3 diff(scale.x() / m_Scale.x(), scale.y() / m_Scale.y(), scale.z() / m_Scale.z());
  m_Scale = scale;
  m_Matrix.scale(diff);
  return *this;
}

Transform& Transform::scale(float x, float y, float z) {
  return scale(math::vec3(x, y, z));
}

Transform& Transform::scale(math::vec3 const& scale) {
  m_Scale += scale;
  m_Matrix.scale(scale);
  return *this;
}

math::vec3 Transform::getScale() const {
  return m_Scale;
}

math::mat4 Transform::matrix() const {
  return m_Matrix;
}

void Transform::updateMatrix() {
  m_Matrix = math::mat4(1).scale(m_Scale).translate(m_Translation).rotate(m_Rotation);
}

}  // namespace engine

}  // namespace orbitals