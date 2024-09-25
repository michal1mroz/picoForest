#ifndef KITTY_H
#define KITTY_H

#include "../../display/InputManager.h"
#include "../MovableEntity.h"
#include <string>

class Kitty : public MovableEntity {
public:
  Kitty(std::shared_ptr<Shader> shader);

  void move(float deltaTime);

private:
  static const std::string meshPath;
  void moveX(float deltaTime);
  void moveY();
  
  // velocity in x-axis on key input
  float stepSizeX = 10.0f; 
  // rate at which kitty decelerate in x-axis with no input
  float decelerationRate = 50.0f; 
};

#endif // KITTY_H
