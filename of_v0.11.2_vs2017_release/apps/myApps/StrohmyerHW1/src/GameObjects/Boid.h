// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_GAMEOBJECTS_BOID_H_
#define STROHMYERHW1_SRC_GAMEOBJECTS_BOID_H_

#include "graphics\ofGraphics.h"

#include "../GameObjects/Physics/Rigidbody.h"
#include "../GameObjects/Physics/SteeringOutput.h"
#include "Crumb.h"

namespace AI {

class Boid {
 public:
  Boid();
  ~Boid();
  void Update(float i_dt);
  void Draw();

  Rigidbody rigidbody;
  SteeringOutput steeringOutput;

  ofColor color = ofColor::blueSteel;
  float radius = 15;

  float maxSpeed = 60.0f;
  float maxRotation = 60.0f;

 private:
  static int16_t const NUM_CRUMBS = 25;
  int16_t crumbCount = 0;
  Crumb crumbs[NUM_CRUMBS];
};

}  // namespace AI

#endif  // STROHMYERHW1_SRC_GAMEOBJECTS_BOID_H_
