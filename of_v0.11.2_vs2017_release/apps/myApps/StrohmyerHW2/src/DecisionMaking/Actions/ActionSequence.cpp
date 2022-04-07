// copyright 2022 Nate Strohmyer

#include "ActionSequence.h"

bool AI::DecisionMaking::ActionSequence::CanInterupt() {
  return actions[0].CanInterupt();
}

bool AI::DecisionMaking::ActionSequence::CanDoBoth(Action const &other) {
  for (size_t i = 0; i < actions.size(); i++) {
    if (!actions[i].CanDoBoth(other)) 
      return false;
  }

  return true;
}

bool AI::DecisionMaking::ActionSequence::IsComplete() {
  return active_action_index >= actions.size();
}

int AI::DecisionMaking::ActionSequence::Execute() {
  int status = actions[active_action_index].Execute();

  if (status == 0 && actions[active_action_index].IsComplete()) {
    active_action_index++;
  }

  return status;
}
