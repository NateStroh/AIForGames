#include "FlagInRangeDecision.h"

#include "ofMath.h"

AI::DecisionMaking::FlagInRangeDecision::FlagInRangeDecision() {
  Boid* boid_ = nullptr;
  ofVec2f* flag_location_ = nullptr;
  float range_ = 50;
  false_node_ = nullptr;
  true_node_ = nullptr;
}

AI::DecisionMaking::FlagInRangeDecision::FlagInRangeDecision(
    Boid* boid_to_track, ofVec2f* flag_location, float range = 50) {
  Boid* boid_ = boid_to_track;
  ofVec2f* flag_location_ = flag_location;
  float range_ = range;
  false_node_ = nullptr;
  true_node_ = nullptr;
}

AI::DecisionMaking::FlagInRangeDecision::FlagInRangeDecision(
    Boid* boid_to_track, ofVec2f* flag_location, DecisionTreeNode* left_node,
    DecisionTreeNode* right_node, float range = 50) {
  Boid* boid_ = boid_to_track;
  ofVec2f* flag_location_ = flag_location;
  float range_ = range;
  false_node_ = left_node;
  true_node_ = right_node;
}

AI::DecisionMaking::DecisionTreeNode*
    AI::DecisionMaking::FlagInRangeDecision::GetBranch() {
  ofVec2f direction = (*flag_location_ - boid_->rigidbody.position);
  float distance = direction.length();

  if (distance <= range_) {
    return true_node_;
  }
  return false_node_;

}
