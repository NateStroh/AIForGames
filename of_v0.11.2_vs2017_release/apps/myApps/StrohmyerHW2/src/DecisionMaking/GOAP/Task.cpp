// copyright 2022 Nate Strohmyer

#include "Task.h"

AI::DecisionMaking::Task::Task() {
  action_to_schedule = nullptr;
}

AI::DecisionMaking::Task::Task(Action* action) {
  action_to_schedule = action;
}

AI::DecisionMaking::Task::~Task() {
  //if (action_to_schedule != nullptr) {
  //  delete action_to_schedule;
  //} 
}
