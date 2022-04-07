// copyright 2022 Nate Strohmyer

#include "ActionCombination.h"

bool AI::DecisionMaking::ActionCombination::CanInterupt() { 
  for (size_t i=0; i < actions.size(); i++) {
    if (actions[i].CanInterupt()) 
      return true;
  }

  return false;
}

bool AI::DecisionMaking::ActionCombination::CanDoBoth(Action const &other) {
  for (size_t i=0; i<actions.size(); i++) {
    if (!actions[i].CanDoBoth(other))
      return false;
  }

  return true;
}

bool AI::DecisionMaking::ActionCombination::IsComplete() {
  for (size_t i=0; i < actions.size(); i++) {
    if (!actions[i].IsComplete())
      return false;
  }

  return true;
}

int AI::DecisionMaking::ActionCombination::Execute() {
  int status = 0;

  for (size_t i=0; i < actions.size(); i++) {
    status = actions[i].Execute();
    if (status != 0) 
      return status;
  }

  return 0;
}
