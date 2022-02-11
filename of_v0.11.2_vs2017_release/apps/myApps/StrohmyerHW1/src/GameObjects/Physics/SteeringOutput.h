// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_GAMEOBJECTS_PHYSICS_STEERINGOUTPUT_H_
#define STROHMYERHW1_SRC_GAMEOBJECTS_PHYSICS_STEERINGOUTPUT_H_

#include "of3dGraphics.h"

namespace AI {

struct SteeringOutput {
  ofVec2f linearAcceleration;
  float rotationAcceleration;

  SteeringOutput() : linearAcceleration(0, 0), rotationAcceleration(0) {}

  SteeringOutput(ofVec2f i_linearAcceleration, float i_rotationAcceleration)
      : linearAcceleration(i_linearAcceleration),
        rotationAcceleration(i_rotationAcceleration) {}
};

}  // namespace AI

#endif  // STROHMYERHW1_SRC_GAMEOBJECTS_PHYSICS_STEERINGOUTPUT_H_
