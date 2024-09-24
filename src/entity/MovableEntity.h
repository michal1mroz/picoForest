#ifndef MOVABLEENTITY_H
#define MOVABLEENTITY_H

/*
*  Sort of interface for entities that can move, so it's applicable for 
*  players, npcs etc.
*/

#include "Entity.h"

class MovableEntity : public Entity{
public:
  MovableEntity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
    : Entity(mesh, shader) {}
  MovableEntity(const std::string &meshPath, std::shared_ptr<Shader> shader)
    : Entity(meshPath, shader) {}
  
  virtual void move() = 0;
private:
  glm::vec3 velocity = glm::vec3(0.0f);
  glm::vec3 acceleration = glm::vec3(0.0f);
  bool grounded = true;
};

#endif // MOVABLEENTITY_H
