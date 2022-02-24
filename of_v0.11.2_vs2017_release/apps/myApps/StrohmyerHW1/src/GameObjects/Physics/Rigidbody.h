// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_GAMEOBJECTS_PHYSICS_RIGIDBODY_H_
#define STROHMYERHW1_SRC_GAMEOBJECTS_PHYSICS_RIGIDBODY_H_

#include "of3dGraphics.h"

namespace AI {

struct Rigidbody {
  ofVec2f position;
  float orientation;
  ofVec2f velocity;
  float rotation;
  float mass;
  int path_index;

  Rigidbody()
      : position(0, 0), orientation(0), velocity(0, 0), rotation(0), mass(1) {}

  Rigidbody(ofVec2f i_position, float i_orientation)
      : position(i_position),
        orientation(i_orientation),
        velocity(0, 0),
        rotation(0),
        mass(1),
        path_index(0) {}
};

}  // namespace AI

#endif  // STROHMYERHW1_SRC_GAMEOBJECTS_PHYSICS_RIGIDBODY_H_
