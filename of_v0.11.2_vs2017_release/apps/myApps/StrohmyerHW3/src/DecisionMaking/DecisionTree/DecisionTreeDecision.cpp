// copyright 2022 Nate Strohmyer

#include "DecisionTreeDecision.h"

AI::DecisionMaking::DecisionTreeNode*
AI::DecisionMaking::DecisionTreeDecision::GetBranch() {
  return nullptr;
}

AI::DecisionMaking::DecisionTreeNode*
AI::DecisionMaking::DecisionTreeDecision::MakeDecision() {
  return GetBranch()->MakeDecision();
}
