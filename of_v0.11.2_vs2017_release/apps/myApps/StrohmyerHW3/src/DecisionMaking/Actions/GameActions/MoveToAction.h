#pragma once

#include <iostream>

#include "..\..\..\GameObjects\Boid.h"
#include "..\Action.h"
#include "..\..\..\MovementAlgorithms\MovementAlgorithms.h"
#include "..\..\..\Pathfinding\PathfindingAlgorithms.h"
#include "..\..\..\Pathfinding\ConnectionGraph.h"

namespace AI {

namespace DecisionMaking {

class MoveToAction : public AI::DecisionMaking::Action {
 public:
  Boid* boid_;
  ofVec2f* position_to_seek_;
  AI::PathfindingAlgorithms::ConnectionGraph* cg_graph_;
  float tile_size_;

  MoveToAction();
  MoveToAction(Boid* boid, ofVec2f* position_to_seek,
               AI::PathfindingAlgorithms::ConnectionGraph* cg_graph_,
               float tile_size_);

  bool CanInterupt();
  bool CanDoBoth(Action other);
  bool IsComplete();
  int Execute();

 private:
  std::vector<int> current_path;
};

}  // namespace DecisionMaking

}  // namespace AI
