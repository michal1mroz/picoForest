#ifndef STATICENTITY_H
#define STATICENTITY_H

/*
* Interface for objects that are rendered and have unique properties,
* but do not move.
*/

#include "Entity.h"
#include <memory>

class StaticEntity : public Entity{
public:
  StaticEntity(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
      : Entity(mesh, shader) {}
  StaticEntity(const std::string &meshPath, std::shared_ptr<Shader> shader)
      : Entity(meshPath, shader) {}
};

#endif // STATICENTITY_H
