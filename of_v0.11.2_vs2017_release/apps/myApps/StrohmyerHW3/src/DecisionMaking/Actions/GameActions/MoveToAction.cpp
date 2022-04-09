#include "MoveToAction.h"

#include "ofUtils.h"
#include "MoveToAction.h"

AI::DecisionMaking::MoveToAction::MoveToAction() {
  priority_ = 1;
  queued_time_ = ofGetCurrentTime().getAsMilliseconds();
  expiry_time_ = 10000;
  boid_ = nullptr;
  position_to_seek_ = nullptr;
}

AI::DecisionMaking::MoveToAction::MoveToAction(Boid* boid,
    ofVec2f* position_to_seek, 
    AI::PathfindingAlgorithms::ConnectionGraph* cg_graph,
    float tile_size) {
  priority_ = 1;
  queued_time_ = ofGetCurrentTime().getAsMilliseconds();
  expiry_time_ = 10000;
  boid_ = boid;
  position_to_seek_ = position_to_seek;
  cg_graph_ = cg_graph;
  tile_size_ = tile_size;
}

bool AI::DecisionMaking::MoveToAction::CanInterupt() {
  return false;
}

bool AI::DecisionMaking::MoveToAction::CanDoBoth(Action other) {
  return false;
}

bool AI::DecisionMaking::MoveToAction::IsComplete() {
  return false;
}

int AI::DecisionMaking::MoveToAction::Execute() {
  int seek_pos_row = (position_to_seek_->y / tile_size_);
  int seek_pos_col = (position_to_seek_->x / tile_size_);
  int seek_pos_to_index = ((seek_pos_row * cg_graph_->columns) + seek_pos_col);

  int char_row = (boid_->rigidbody.position.y / tile_size_);
  int char_col = (boid_->rigidbody.position.x / tile_size_);
  int character_pos_to_index = (char_row * cg_graph_->columns) + char_col;

  current_path = AI::PathfindingAlgorithms::AStarSearchMDH(
      cg_graph_,
      cg_graph_->num_nodes,
      character_pos_to_index,
      seek_pos_to_index);
  boid_->steeringOutput.linearAcceleration =
      AI::MovementAlgorithms::FollowPath(
          &boid_->rigidbody,    // character rigidbody
          current_path,         // path to follow - vector<int>
          cg_graph_->columns,   // number of columns
          tile_size_,          // tile size
          55.0f,                // smoothing radius
          20.0f,                // max acceleration
          80.0f,                // max speed
          200.0f,               // slow radius
          5.0f,                 // target radius
          0.01f)
          .linearAcceleration;
  boid_->rigidbody.orientation =
    AI::MovementAlgorithms::KinematicAlign(boid_->rigidbody.velocity)
          .rotationAcceleration;

  return 0;
}
