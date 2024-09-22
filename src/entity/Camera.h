#ifndef CAMERA_H
#define CAMERA_H

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

class Camera {
public:
  Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov,
         float aspectRatio, float nearPlane, float farPlane);
  
  glm::mat4 getViewMatrix() const { return viewMatrix; }
  glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
  glm::vec3 getPosition() const {return position;}
  void setPosition(const glm::vec3 &pos);
  void setTarget(const glm::vec3 &tgt);
  void setUpVector(const glm::vec3 &upVec);
  void setFov(float fov);
  void setAspectRatio(float ratio);
  void setNearPlane(float nearPlane);
  void setFarPlane(float farPlane);

private:
  glm::vec3 position;
  glm::vec3 target;
  glm::vec3 up;
  float fov;
  float aspectRatio;
  float nearPlane;
  float farPlane;

  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;

  void updateViewMatrix();
  void updateProjectionMatrix();
};

#endif // CAMERA_H
