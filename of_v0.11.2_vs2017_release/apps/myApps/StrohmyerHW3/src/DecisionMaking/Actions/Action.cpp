// copyright 2022 Nate Strohmyer

#include "Action.h"

bool AI::DecisionMaking::Action::CanInterupt() { return false; }

bool AI::DecisionMaking::Action::CanDoBoth(Action other) { return false; }

bool AI::DecisionMaking::Action::IsComplete() { return true; }

int AI::DecisionMaking::Action::Execute() { return 0; }

bool AI::DecisionMaking::Action::operator<(const Action& other) const {
  return (priority_ < other.priority_);
}
