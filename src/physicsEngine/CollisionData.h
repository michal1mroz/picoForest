#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <ostream>
enum DIRECTION { UP, RIGHT, DOWN, LEFT };

struct CollisionData {
  bool collisions[4] = {false};
  float distanceToWall[4] = {0.0f};

  friend std::ostream &operator<<(std::ostream &COUT,
                                  const CollisionData &data);
};

#endif // COLLISIONDATA_H
