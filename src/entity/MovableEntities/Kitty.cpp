#include "Kitty.h"

const std::string Kitty::meshPath = "resources/kitty/kitty.obj";

Kitty::Kitty(std::shared_ptr<Shader> shader)
    : MovableEntity(meshPath, shader) {}

void Kitty::move(float deltaTime) {
  moveX(deltaTime);
  moveY();
}

void Kitty::moveY(){
  auto input = InputManager::getInstance();
  auto vel = this->getVelocity();
  if(getGrounded() && input.isCommandActive(InputManager::MAIN_MOVE_UP)){
    vel.y = 15* stepSizeX;
    setGrounded(false);
  }
  else if(input.isCommandActive(InputManager::MAIN_MOVE_DOWN)){
    vel.y = -stepSizeX;
  }
  else{
    vel.y = 0;
  }
  this->setVelocity(vel);
}

void Kitty::moveX(float deltaTime){
  auto& input = InputManager::getInstance();
  auto oldVelocity = this->getVelocity();
  if(input.isCommandActive(InputManager::MAIN_MOVE_LEFT)){
    oldVelocity.x = -stepSizeX;
  }
  else if(input.isCommandActive(InputManager::MAIN_MOVE_RIGHT)){
    oldVelocity.x = stepSizeX;
  }
  else{
    auto oldAcceleration = this->getAcceleration();
    if(oldVelocity.x > 0){
      oldVelocity.x -= decelerationRate * deltaTime;
      if(oldVelocity.x < 0) oldVelocity.x = 0;
    }
    else if(oldVelocity.x < 0){
      oldVelocity.x += decelerationRate * deltaTime;
      if(oldVelocity.x > 0) oldVelocity.x = 0;
    }
     
  }
  this->setVelocity(oldVelocity);
}
