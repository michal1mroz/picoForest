#include "Entity.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
    : mesh{mesh}, shader{shader} {}

glm::mat4 Entity::getModelMatrix() const {

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, this->position);
  model = glm::rotate(model, glm::radians(this->rotation.x),
                      glm::vec3(1.0f, 0.0f, 0.0f));
  model = glm::rotate(model, glm::radians(this->rotation.y),
                      glm::vec3(0.0f, 1.0f, 0.0f));
  model = glm::rotate(model, glm::radians(this->rotation.z),
                      glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, this->scale);
  return model;
}

void Entity::draw() const {
  if (!shader || !mesh)
    return;

  glm::mat4 model = getModelMatrix();
  shader->use();

  shader->setUniform("model", model);

  mesh->render();
}

std::size_t Entity::getHash() const {
  return std::hash<unsigned int>{}(shader->getProgramID());
}
