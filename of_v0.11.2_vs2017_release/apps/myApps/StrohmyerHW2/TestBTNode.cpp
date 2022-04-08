#include "TestBTNode.h"

TestBTNode::TestBTNode() {
  action_ = nullptr;
}

TestBTNode::TestBTNode(AI::DecisionMaking::Action* action_to_schedule) {
  action_ = action_to_schedule;
}

TestBTNode::~TestBTNode() {
  //if (action_ != nullptr)
  //  delete action_;
}

AI::DecisionMaking::BTTick TestBTNode::Run(AI::DecisionMaking::BTTick tick) {
  tick.action_to_schedule_ = action_;
  tick.status_ = 0;
  return tick;
}
