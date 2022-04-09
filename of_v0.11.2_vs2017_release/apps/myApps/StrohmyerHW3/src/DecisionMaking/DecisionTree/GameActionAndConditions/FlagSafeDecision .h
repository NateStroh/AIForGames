#pragma once

#include "..\DecisionTreeDecision.h"

namespace AI {

namespace DecisionMaking {

class FlagSafeDecision : public AI::DecisionMaking::DecisionTreeDecision {
 public:
  bool* isFlagTaken_;

  FlagSafeDecision();
  FlagSafeDecision(bool* flag_status);
  FlagSafeDecision(bool* flag_status,
                   DecisionTreeNode* left_node,
                   DecisionTreeNode* right_node);
  DecisionTreeNode* GetBranch();
};

}  // namespace DecisionMaking

}  // namespace AI
