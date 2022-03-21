// copyright 2022 Nate Strohmyer

#include "ActionCombination.h"

bool AI::DecisionMaking::ActionCombination::CanInterupt() { 
  for (Action action : actions) {
    if (action.CanInterupt())
      return true;
  }

  return false;
}

bool AI::DecisionMaking::ActionCombination::CanDoBoth(Action other) {
  for (Action action : actions) {
    if (!action.CanDoBoth(other))
      return false;
  }

  return true;
}

bool AI::DecisionMaking::ActionCombination::IsComplete() {
  for (Action action : actions) {
    if (!action.IsComplete())
      return false;
  }

  return true;
}

int AI::DecisionMaking::ActionCombination::Execute() {
  int status = 0;
  for (Action action : actions) {
    status = action.Execute();
    if (status != 0)
      return status;
  }

  return 0;
}
