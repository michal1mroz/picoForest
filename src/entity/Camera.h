#ifndef CAMERA_H
#define CAMERA_H

#include "../display/InputManager.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

class Camera {
public:
  Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov,
         float aspectRatio, float nearPlane, float farPlane);

  void handleMouseDrag();

  glm::mat4 getViewMatrix() const { return viewMatrix; }
  glm::mat4 getProjectionMatrix() const { return projectionMatrix; }
  glm::vec3 getPosition() const { return position; }
  void setPosition(const glm::vec3 &pos);
  void setTarget(const glm::vec3 &tgt);
  void setUpVector(const glm::vec3 &upVec);
  void setFov(float fov);
  void setAspectRatio(float ratio);
  void setNearPlane(float nearPlane);
  void setFarPlane(float farPlane);

  void setRadius(double newRadius){radius = newRadius;};
  double getRadius(){return radius;};
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

  double radius = 20.0;
  double azimuth = 0.0;
  double elevation = 0.0;
  double sensitivity = 0.005;
  glm::vec2 lastMousePosition = glm::vec2(0.0f);
  bool mouseLeftFirst = true;

  void updateViewMatrix();
  void updateProjectionMatrix();
  void moveCamera(glm::vec2 delta);
};

#endif // CAMERA_H
