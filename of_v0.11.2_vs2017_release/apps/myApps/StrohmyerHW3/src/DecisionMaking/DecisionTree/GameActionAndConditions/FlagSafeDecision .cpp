#include "FlagSafeDecision .h"

AI::DecisionMaking::FlagSafeDecision::FlagSafeDecision() {
  isFlagTaken_ = nullptr;
}

AI::DecisionMaking::FlagSafeDecision::FlagSafeDecision(bool* flag_status) {
  isFlagTaken_ = flag_status;
}

AI::DecisionMaking::FlagSafeDecision::FlagSafeDecision(
    bool* flag_status, DecisionTreeNode* left_node,
    DecisionTreeNode* right_node) {
  isFlagTaken_ = flag_status;
  false_node_ = left_node;
  true_node_ = right_node;
}

AI::DecisionMaking::DecisionTreeNode*
    AI::DecisionMaking::FlagSafeDecision::GetBranch() {
  if ((*isFlagTaken_)) {
    return false_node_;
  }
  return true_node_;
}
