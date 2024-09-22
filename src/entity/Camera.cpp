#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up, float fov,
               float aspectRatio, float nearPlane, float farPlane)
    : position{position}, target{target}, up{up}, fov{fov},
      aspectRatio{aspectRatio}, nearPlane{nearPlane}, farPlane{farPlane} {
  updateViewMatrix();
  updateProjectionMatrix();
}

void Camera::setPosition(const glm::vec3 &pos) {
  this->position = pos;
  updateViewMatrix();
}
void Camera::setTarget(const glm::vec3 &tgt) {
  this->target = tgt;
  updateViewMatrix();
}
void Camera::setUpVector(const glm::vec3 &upVec) {
  this->up = upVec;
  updateViewMatrix();
}
void Camera::setFov(float fov) {
  this->fov = fov;
  updateProjectionMatrix();
}
void Camera::setAspectRatio(float ratio) {
  this->aspectRatio = ratio;
  updateProjectionMatrix();
}
void Camera::setNearPlane(float nearPlane) {
  this->nearPlane = nearPlane;
  updateProjectionMatrix();
}
void Camera::setFarPlane(float farPlane) {
  this->farPlane = farPlane;
  updateProjectionMatrix();
}

void Camera::updateViewMatrix() {
  this->viewMatrix = glm::lookAt(this->position, this->target, this->up);
}

void Camera::updateProjectionMatrix() {
  this->projectionMatrix = glm::perspective(
      glm::radians(fov), this->aspectRatio, this->nearPlane, this->farPlane);
}

