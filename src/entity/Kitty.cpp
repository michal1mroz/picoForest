#include "Kitty.h"

const std::string Kitty::meshPath = "resources/kitty/kitty.obj";

Kitty::Kitty(std::shared_ptr<Shader> shader)
    : Entity(meshPath, shader) {}

void Kitty::move() {
      
}
