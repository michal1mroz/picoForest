#ifndef ENTITY_H
#define ENTITY_H

/*
* Base class for objects that are rendered with mesh and shader
*/

#include "../meshes/Mesh.h"
#include "../meshes/MeshManager.h"
#include "../shaders/Shader.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <memory>

class Entity {
public:
  Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
  Entity(const std::string &meshPath, std::shared_ptr<Shader> shader);

  const glm::vec3 &getPosition() const { return position; }
  void setPosition(const glm::vec3 &pos) {
    position = pos;
    modelMatrix = getModelMatrix();
  }

  const glm::vec3 &getRotation() const { return rotation; }
  void setRotation(const glm::vec3 &rot) {
    rotation = rot;
    modelMatrix = getModelMatrix();
  }

  const glm::vec3 &getScale() const { return scale; }
  void setRotation(const glm::vec4 &scl) {
    scale = scl;
    modelMatrix = getModelMatrix();
  }

  const std::shared_ptr<Shader> getShader() const { return this->shader; }
  virtual void draw() const;
  std::size_t getHash() const;

  unsigned int getID() const {return entityID;}
  bool operator==(const Entity& other);
private:
  glm::mat4 getModelMatrix() const;

  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Shader> shader;

  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
  glm::mat4 modelMatrix;

  static unsigned int ID_COUNTER;
  unsigned int entityID;
};

#endif // ENTITY_H
