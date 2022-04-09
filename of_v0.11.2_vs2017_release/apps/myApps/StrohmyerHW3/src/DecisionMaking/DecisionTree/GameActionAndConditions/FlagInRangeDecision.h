#pragma once

#include "..\..\..\GameObjects\Boid.h"
#include "..\DecisionTreeDecision.h"

namespace AI {

namespace DecisionMaking {

class FlagInRangeDecision
    : public AI::DecisionMaking::DecisionTreeDecision {
 public:
  Boid* boid_;
  ofVec2f* flag_location_;
  float range_;

  FlagInRangeDecision();
  FlagInRangeDecision(Boid* boid_to_track,
                           ofVec2f* flag_location,
                           float range);
  FlagInRangeDecision(Boid* boid_to_track, ofVec2f* flag_location,
                           DecisionTreeNode* left_node, 
                           DecisionTreeNode* right_node,
                           float range);
  DecisionTreeNode* GetBranch();
};

}  // namespace DecisionMaking

}  // namespace AI
