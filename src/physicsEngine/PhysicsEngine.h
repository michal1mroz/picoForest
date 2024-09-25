#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include "../entity/MovableEntity.h"
#include "../entity/StaticEntity.h"
#include "CollisionData.h"

#include <memory>
#include <vector>

class PhysicsEngine {
public:
  static void
  Update(float deltaTime,
         std::vector<std::shared_ptr<MovableEntity>> &movableEntities,
         std::vector<std::shared_ptr<Entity>> &staticEntities);

private:
  static void ApplyGravity(float timeDelta,
                           std::shared_ptr<MovableEntity> entity);
  static CollisionData
  DetectCollisions(std::shared_ptr<MovableEntity> movable,
                   std::vector<std::shared_ptr<Entity>> staticEntities,
                   glm::vec3 newPosition);

  static void CheckOneCollision(std::shared_ptr<MovableEntity> entity1,
                                std::shared_ptr<Entity> entity2,
                                glm::vec3 moveVector, CollisionData &data);

  static const float GRAVITY_CONSTANT;
};

#endif // PHYSICSENGINE_H
