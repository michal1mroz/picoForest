#include "Kitty.h"

const std::string Kitty::meshPath = "resources/kitty/kitty.obj";

Kitty::Kitty(std::shared_ptr<Shader> shader)
    : Entity(meshPath, shader) {}

void Kitty::move() {
  auto input = InputManager::getInstance();
  auto position = this->getPosition();
  if(input.isCommandActive(InputManager::MAIN_MOVE_UP)){
    position.y += 0.5f;
    this->setPosition(position);
  }
  if(input.isCommandActive(InputManager::MAIN_MOVE_DOWN)){
    position.y -= 0.5f;
    this->setPosition(position);
  }
  if(input.isCommandActive(InputManager::MAIN_MOVE_LEFT)){
    position.x -= 0.5f;
    this->setPosition(position);
  }
  if(input.isCommandActive(InputManager::MAIN_MOVE_RIGHT)){
    position.x += 0.5f;
    this->setPosition(position);
  }
}
