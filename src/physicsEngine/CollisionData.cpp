#include "CollisionData.h"

std::ostream &operator<<(std::ostream &COUT, const CollisionData &data) {
  COUT << "Collisions:\nUP: " << data.collisions[UP] << " RIGHT: " << data.collisions[RIGHT];
  COUT << " DOWN: " << data.collisions[DOWN]
       << " LEFT: " << data.collisions[LEFT] << std::endl;
  COUT << " Distances:\nUP: " <<data.distanceToWall[UP] << " RIGHT: " <<data.distanceToWall[RIGHT];
  COUT << " DOWN: " <<data.distanceToWall[DOWN] << " LEFT: " <<data.distanceToWall[LEFT] << std::endl;
  return COUT;
}
