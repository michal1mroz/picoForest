#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

/*
 *  Sort of interface for entities that can move, so it's applicable for
 *  players, npcs etc.
 */

#include "Entity.h"

class MovableEntity : public Entity {
public:
  MovableEntity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
      : Entity(mesh, shader) {}
  MovableEntity(const std::string &meshPath, std::shared_ptr<Shader> shader)
      : Entity(meshPath, shader) {}

  virtual void move(float deltaTime) = 0;

  void setVelocity(glm::vec2 newVelocity) { velocity = newVelocity; }
  glm::vec2 getVelocity() { return velocity; }
  void setAcceleration(glm::vec2 newAcceleration) {
    acceleration = newAcceleration;
  }
  glm::vec2 getAcceleration() { return acceleration; }
  void setGrounded(bool newGrounded) { grounded = newGrounded; }
  bool getGrounded() { return grounded; }

private:
  glm::vec2 velocity = glm::vec2(0.0f);
  glm::vec2 acceleration = glm::vec2(0.0f);
  bool grounded = true;
};

#endif // MOVABLEENTITY_H
