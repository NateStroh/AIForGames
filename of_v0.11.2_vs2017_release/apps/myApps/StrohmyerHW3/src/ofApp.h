// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_OFAPP_H_
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_OFAPP_H_

#include <string>
#include <vector>

#include "DecisionMaking\Actions\ActionManager.h"
#include "GameObjects\Boid.h"
#include "Pathfinding\ConnectionGraph.h"
#include "ofMain.h"

#include "DecisionMaking\BehaviorTree\BehaviorTree.h"
#include "DecisionMaking\DecisionTree\DecisionTree.h"
#include "DecisionMaking\GOAP\GOAP.h"

#include "DecisionMaking\Actions\GameActions\MoveToAction.h"

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
  AI::PathfindingAlgorithms::ConnectionGraph ReadInGraph(std::string file_path);
  void PrintVector(vector<int> path);

  AI::Boid leadBoid;
  AI::Boid monsterBoid;
  int16_t corner = 0;
  bool draw_grid = false;
  bool draw_blocked_tiles = false;
  bool draw_walls = true;
  int rows = 15;
  int columns = 20;
  float tile_size = 51.0f;

  float grid_thickness = 5.0f;
  ofVec2f clickLocation = {500, 500};
  AI::PathfindingAlgorithms::ConnectionGraph cg_graph;
  std::vector<int> current_path;

  std::vector<int> tilesblocked = {
      12,  13,  14,  15,  35,  37,  55,  56,  57,  67,  71,  75,  87,  91,  102,
      103, 107, 108, 109, 110, 111, 122, 123, 162, 163, 182, 183, 189, 195, 196,
      197, 198, 202, 203, 204, 205, 206, 209, 215, 216, 217, 218, 222, 223, 224,
      225, 226, 229, 235, 236, 237, 238, 249, 255, 256, 257, 258, 260, 261, 262,
      263, 264, 265, 266, 267, 269, 275, 276, 277, 278, 289};

  AI::DecisionMaking::ActionManager action_manager;
  AI::DecisionMaking::DecisionTree DT;
  AI::DecisionMaking::BehaviorTree BT;
  AI::DecisionMaking::GOAP goap;
  
  AI::DecisionMaking::MoveToAction MTA = *new AI::DecisionMaking::MoveToAction(
      &monsterBoid,
      &(leadBoid.rigidbody.position),
      &cg_graph,
      tile_size
  );

};

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_OFAPP_H_
