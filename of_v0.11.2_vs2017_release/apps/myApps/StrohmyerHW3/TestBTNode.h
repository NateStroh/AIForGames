#pragma once

#include "src\DecisionMaking\BehaviorTree\BehaviorTreeNode.h"
#include "src\DecisionMaking\Actions\Action.h"

class TestBTNode : public AI::DecisionMaking::BehaviorTreeNode {
 public:
  AI::DecisionMaking::Action* action_; 
  
  TestBTNode();
  TestBTNode(AI::DecisionMaking::Action* action_to_schedule);
  ~TestBTNode();
  AI::DecisionMaking::BTTick Run(AI::DecisionMaking::BTTick tick);  
};
