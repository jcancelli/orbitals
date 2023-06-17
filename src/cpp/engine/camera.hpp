#pragma once

#include "../math/matrix.hpp"

namespace orbitals {

namespace engine {

class Camera {
 protected:
  math::vec3 m_Position;
  math::vec3 m_Center;
  math::vec3 m_UpVector;
  math::mat4 m_CameraMatrix, m_ViewMatrix, m_ProjectionMatrix;
  float m_ZNear, m_ZFar;

 public:
  Camera();
  Camera(float x, float y, float z);
  Camera(math::vec3 const& position);
  void lookAt(float x, float y, float z);
  void lookAt(math::vec3 const& center);
  void translate(float x, float y, float z);
  void translate(math::vec3 const& amount);
  void translateX(float x);
  void translateY(float y);
  void translateZ(float z);
  void setPosition(float x, float y, float z);
  void setPosition(math::vec3 const& position);
  void setX(float x);
  void setY(float y);
  void setZ(float z);
  void setUpVector(math::vec3 const& upVector);
  void setZNear(float zNear);
  void setZFar(float zFar);
  math::vec3 getPosition() const;
  float getX() const;
  float getY() const;
  float getZ() const;
  float getZNear() const;
  float getZFar() const;
  math::mat4 getCameraMatrix() const;
  math::mat4 getViewMatrix() const;
  math::mat4 getProjectionMatrix() const;

 protected:
  void updateCameraMatrix();
  void updateViewMatrix(bool updateCameraMatrix = true);
  virtual void updateProjectionMatrix(bool updateCameraMatrix = true) = 0;
};

class OrthograficCamera : public Camera {
 protected:
  float m_Left, m_Right, m_Bottom, m_Top;

 public:
  OrthograficCamera();
  OrthograficCamera(float x, float y, float z, float left, float right, float bottom, float top);
  OrthograficCamera(math::vec3 const& position, float left, float right, float bottom, float top);
  void setLeft(float left);
  void setRight(float right);
  void setBottom(float bottom);
  void setTop(float top);
  float getLeft() const;
  float getRight() const;
  float getBottom() const;
  float getTop() const;

 protected:
  void updateProjectionMatrix(bool updateCameraMatrix = true) override;
};

class PerspectiveCamera : public Camera {
 protected:
  float m_FOV;
  float m_AspectRatio;

 public:
  PerspectiveCamera();
  PerspectiveCamera(float x, float y, float z, float fov, float aspectRatio);
  PerspectiveCamera(math::vec3 const& position, float fov, float aspectRatio);
  void setFOV(float fov);
  void setAspectRatio(float aspectRatio);
  float getFOV() const;
  float getAspectRatio() const;

 protected:
  void updateProjectionMatrix(bool updateCameraMatrix = true) override;
};

}  // namespace engine

}  // namespace orbitals