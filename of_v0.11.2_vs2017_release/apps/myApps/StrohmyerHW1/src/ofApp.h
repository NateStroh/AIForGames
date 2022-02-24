// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_OFAPP_H_
#define STROHMYERHW1_SRC_OFAPP_H_

#include <vector>

#include "GameObjects\Boid.h"
#include "Pathfinding\ConnectionGraph.h"
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
  AI::PathfindingAlgorithms::ConnectionGraph ReadInGraph(std::string file_path);

  AI::Boid leadBoid;
  std::vector<AI::Boid> flock;
  int16_t mode = 0;
  int16_t corner = 0;
  int16_t modeChanges = 1;

  int rows = 15;
  int columns = 20;
  float tile_size = 51.0f;

  // int rows = 5;
  // int columns = 5;
  // float tile_size = 100.0f;

  float grid_thickness = 5.0f;
  ofVec2f clickLocation = {500, 500};
  std::vector<int> testPath = {0,  1,  2,  3,  4,  9,  8,  7,  6,
                               5,  10, 11, 12, 13, 14, 19, 18, 17,
                               16, 15, 20, 21, 22, 23, 24};
  AI::PathfindingAlgorithms::ConnectionGraph cg_graph;
  std::vector<int> current_path;

  std::vector<int> tilesblocked = {
      12,  13,  14,  15,  35,  37,  55,  56,  57,  67,  71,  75,  87,  91,  102,
      103, 107, 108, 109, 110, 111, 122, 123, 162, 163, 182, 183, 189, 195, 196,
      197, 198, 202, 203, 204, 205, 206, 209, 215, 216, 217, 218, 222, 223, 224,
      225, 226, 229, 235, 236, 237, 238, 249, 255, 256, 257, 258, 260, 261, 262,
      263, 264, 265, 266, 267, 269, 275, 276, 277, 278, 289};
};

#endif  // STROHMYERHW1_SRC_OFAPP_H_
