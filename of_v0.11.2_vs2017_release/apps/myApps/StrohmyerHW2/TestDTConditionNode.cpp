#include "TestDTConditionNode.h"

#include "ofMath.h"

TestDTConditionNode::DecisionTreeNode* TestDTConditionNode::GetBranch() {
  float random = ofRandomuf();
  if (random > .5) 
    return true_node_;
  return false_node_;
}
