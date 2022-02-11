// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_GAMEOBJECTS_CRUMB_H_
#define STROHMYERHW1_SRC_GAMEOBJECTS_CRUMB_H_

#include "graphics\ofGraphics.h"
#include "ofTimer.h"

namespace AI {

class Crumb {
 public:
  Crumb();
  explicit Crumb(glm::vec2 i_startingPosition);
  ~Crumb();
  void Update(double i_dt);
  void Draw();

 private:
  glm::vec2 position;
  ofTime startTime;
};

}  // namespace AI

#endif  // STROHMYERHW1_SRC_GAMEOBJECTS_CRUMB_H_
