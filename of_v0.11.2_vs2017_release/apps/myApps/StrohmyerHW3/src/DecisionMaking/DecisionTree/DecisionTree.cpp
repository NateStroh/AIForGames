// copyright 2022 Nate Strohmyer

#include "DecisionTree.h"

#include "DecisionTreeAction.h"

bool AI::DecisionMaking::DecisionTree::MakeDecision() {
  // get action to schedule
  Action* action_to_schedule = dynamic_cast<DecisionTreeAction*>(root_node_->MakeDecision())->action;
  
  // check if that action is valid
  if (action_to_schedule == nullptr) {
    return false;
  }

  // FIXME!!! this will need to be newed - this will go out of scope
  action_manager_->ScheduleAction(action_to_schedule);
  return true;
}

void AI::DecisionMaking::DecisionTree::ConnectNodes(int parent_node_index,
                                                    int child_node_index,
                                                    bool is_left_node) {
  if (is_left_node) 
    decision_tree_nodes_[child_node_index];
  else {
    decision_tree_nodes_[child_node_index];
  }
}
