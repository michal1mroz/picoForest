#ifndef LIGHT_H
#define LIGHT_H

#include <glm/ext/vector_float3.hpp>

class Light {
public:
  Light(glm::vec3 position, glm::vec3 color);

  const glm::vec3 getPosition() const;
  const glm::vec3 getColour() const;

  void setPosition(const glm::vec3 &position);
  void setColour(const glm::vec3 &colour);

private:
  glm::vec3 position;
  glm::vec3 colour;
};

#endif // LIGHT_H
