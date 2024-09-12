#ifndef ENTITY_H
#define ENTITY_H

#include "../meshes/Mesh.h"
#include "../shaders/Shader.h"
#include <memory>

class Entity {
public:
  Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader);
  
  const glm::vec3& getPosition() const {return position;}
  void setPosition(const glm::vec3& pos) {position = pos;}

  const glm::vec3& getRotation() const {return rotation;}
  void setRotation(const glm::vec3& rot) {rotation = rot;}

  const glm::vec3& getScale() const {return scale;}
  void setRotation(const glm::vec4& scl) {scale = scl;}

  void draw() const;
  std::size_t getHash() const;
private:
  glm::mat4 getModelMatrix() const;

  std::shared_ptr<Mesh> mesh;
  std::shared_ptr<Shader> shader;

  glm::vec3 position = glm::vec3(1.0f, 1.0f, -2.0f);
  glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 scale = glm::vec3(1.0f,1.0f, 1.0f);
};

#endif // ENTITY_H