// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_GAMEOBJECTS_PHYSICS_STEERINGOUTPUT_H_
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_GAMEOBJECTS_PHYSICS_STEERINGOUTPUT_H_

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

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_GAMEOBJECTS_PHYSICS_STEERINGOUTPUT_H_
