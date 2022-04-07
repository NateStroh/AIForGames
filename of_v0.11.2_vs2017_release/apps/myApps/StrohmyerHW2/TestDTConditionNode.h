#pragma once

#include "src\DecisionMaking\DecisionTree\DecisionTreeDecision.h"

class TestDTConditionNode : public AI::DecisionMaking::DecisionTreeDecision{
 public:
  DecisionTreeNode* GetBranch();
};
