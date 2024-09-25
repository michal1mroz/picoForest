#include "Entity.h"

unsigned int Entity::ID_COUNTER = 0;

Entity::Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
    : mesh{mesh}, shader{shader}, modelMatrix{getModelMatrix()} {
  entityID = ++ID_COUNTER;
}

Entity::Entity(const std::string &meshPath, std::shared_ptr<Shader> shader)
    : modelMatrix{getModelMatrix()} {
  this->mesh = MeshManager::getInstance().getMesh(meshPath);
  this->shader = shader;
  entityID = ++ID_COUNTER;
}



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

  shader->setUniform("model", modelMatrix);

  mesh->render();
}

std::size_t Entity::getHash() const {
  return std::hash<unsigned int>{}(shader->getProgramID());
}

bool Entity::operator==(const Entity& other){
  return (this->getID() == other.getID());
}
