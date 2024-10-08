#ifndef KITTY_H
#define KITTY_H

#include "../display/InputManager.h"
#include "Entity.h"
#include <string>

class Kitty : public Entity {
public:
  Kitty(std::shared_ptr<Shader> shader);

  void move();

private:
  static const std::string meshPath;
  const std::shared_ptr<MainDisplay> display; // Needed for movement
};

#endif // KITTY_H
