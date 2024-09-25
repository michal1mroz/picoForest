#include "PhysicsEngine.h"

const float PhysicsEngine::GRAVITY_CONSTANT = 10.0f;

void PhysicsEngine::Update(
    float deltaTime,
    std::vector<std::shared_ptr<MovableEntity>> &movableEntities,
    std::vector<std::shared_ptr<Entity>> &staticEntities) {

  for (auto &movable : movableEntities) {
    movable->move(deltaTime);
    if (!movable->getGrounded())
      ApplyGravity(deltaTime, movable);

    glm::vec2 velocity = movable->getVelocity();
    glm::vec2 acceleration = movable->getAcceleration();
    auto position = movable->getPosition();

    velocity += acceleration * deltaTime;
    glm::vec3 newPosition = position + glm::vec3(velocity, 0.0f) * deltaTime;
    auto moveVector = newPosition - position;

    auto data = DetectCollisions(movable, staticEntities, moveVector);
    if (data.collisions[RIGHT] && moveVector.x > 0) {
      moveVector.x = data.distanceToWall[RIGHT];
      velocity.x = 0;
    }
    if (data.collisions[LEFT] && moveVector.x < 0) {
      moveVector.x = data.distanceToWall[LEFT];
      velocity.x = 0;
    }
    if (data.collisions[UP] && moveVector.y > 0) {
      moveVector.y = data.distanceToWall[UP];
      velocity.y = 0;
    }
    if (data.collisions[DOWN] && moveVector.y < 0) {
      moveVector.y = data.distanceToWall[DOWN];
      velocity.y = 0;
      movable->setGrounded(true);
    }

    movable->setVelocity(velocity);
    movable->setPosition(position + moveVector);
  }
}

void PhysicsEngine::ApplyGravity(float timeData,
                                 std::shared_ptr<MovableEntity> entity) {
  auto velocity = entity->getVelocity();
  velocity.y -= 200.0f * timeData;
  entity->setVelocity(velocity);
}

/*
 * Implementation of AABB vs AABB collision detection.
 * For now we assume collisions to happen in 2d space
 * (objects cannot move in z-axis).
 * Collisions don't take cats ears into consideration,
 * also assuming that the default objects size is 2 and not 1
 * (base cubes drawn from (-1,-1) to (1,1))
 */

void PhysicsEngine::CheckOneCollision(std::shared_ptr<MovableEntity> entity1,
                                      std::shared_ptr<Entity> entity2,
                                      glm::vec3 moveVector,
                                      CollisionData &collisionsTracker) {
  auto movableMin = entity1->getPosition() - entity1->getScale();
  auto movableMax = entity1->getPosition() + entity1->getScale();
  auto staticMin = entity2->getPosition() - entity2->getScale();
  auto staticMax = entity2->getPosition() + entity2->getScale();

  bool overlapX = movableMax.x > staticMin.x && movableMin.x < staticMax.x;
  bool overlapY = movableMax.y > staticMin.y && movableMin.y < staticMax.y;

  if (overlapY) {
    if (movableMax.x + moveVector.x > staticMin.x &&
        movableMin.x < staticMin.x) {
      collisionsTracker.collisions[RIGHT] = true;
      collisionsTracker.distanceToWall[RIGHT] = staticMin.x - movableMax.x;
    }
    if (movableMin.x + moveVector.x < staticMax.x &&
        movableMax.x > staticMax.x) {
      collisionsTracker.collisions[LEFT] = true;
      collisionsTracker.distanceToWall[LEFT] = staticMax.x - movableMin.x;
    }
  }
  if (overlapX) {
    if (movableMax.y + moveVector.y > staticMin.y &&
        movableMin.y < staticMin.y) {
      collisionsTracker.collisions[UP] = true;
      collisionsTracker.distanceToWall[UP] = staticMin.y - movableMax.y;
    }
    if (movableMin.y + moveVector.y < staticMax.y &&
        movableMax.y > staticMax.y) {
      collisionsTracker.collisions[DOWN] = true;
      collisionsTracker.distanceToWall[DOWN] = staticMax.y - movableMin.y;
    }
  }
}

CollisionData PhysicsEngine::DetectCollisions(
    std::shared_ptr<MovableEntity> movable,
    std::vector<std::shared_ptr<Entity>> staticEntities, glm::vec3 moveVector) {
  CollisionData data;
  for (auto &entity : staticEntities) {
    if (entity == movable)
      continue;
    CheckOneCollision(movable, entity, moveVector, data);
  }
  return data;
}


