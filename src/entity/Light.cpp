#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 colour) 
  : position{position}, colour{colour}
  {}

const glm::vec3 Light::getPosition() const {
  return this->position;
}
const glm::vec3 Light::getColour() const {
  return this->colour;
}

void Light::setPosition(const glm::vec3 &position) {
  this->position = position;
}
void Light::setColour(const glm::vec3 &colour) {
  this->colour = colour;
}
