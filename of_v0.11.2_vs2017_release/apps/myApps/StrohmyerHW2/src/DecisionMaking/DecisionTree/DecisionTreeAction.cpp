// copyright 2022 Nate Strohmyer

#include "DecisionTreeAction.h"

AI::DecisionMaking::DecisionTreeNode*
AI::DecisionMaking::DecisionTreeAction::MakeDecision() {
  return this;
}

AI::DecisionMaking::DecisionTreeAction::DecisionTreeAction() {
  action = nullptr;
}

AI::DecisionMaking::DecisionTreeAction::DecisionTreeAction(
    Action action_to_add){
    action = new Action(action_to_add);
}

AI::DecisionMaking::DecisionTreeAction::~DecisionTreeAction() { 
  if (action != nullptr) {
    delete action;
  }
}
