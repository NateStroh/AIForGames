// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_OFAPP_H_
#define STROHMYERHW1_SRC_OFAPP_H_

#include <vector>

#include "GameObjects\Boid.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

 private:
  std::vector<AI::Rigidbody> GetRigidbodies(std::vector<AI::Boid> i_boids);
  ofVec2f GoToCorner(int i_corner, AI::Boid i_boidToMove);

  AI::Boid leadBoid;
  std::vector<AI::Boid> flock;
  int16_t mode = 0;
  int16_t corner = 0;
  int16_t modeChanges = 1;

  ofVec2f clickLocation;
};

#endif  // STROHMYERHW1_SRC_OFAPP_H_
