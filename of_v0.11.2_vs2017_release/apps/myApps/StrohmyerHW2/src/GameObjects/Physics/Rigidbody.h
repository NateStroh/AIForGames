// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_GAMEOBJECTS_PHYSICS_RIGIDBODY_H_
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_GAMEOBJECTS_PHYSICS_RIGIDBODY_H_

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

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_GAMEOBJECTS_PHYSICS_RIGIDBODY_H_
