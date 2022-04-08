#include "MoveToMyFlagAction.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::MoveToMyFlagAction::Run(
    BTTick tick) {
  tick.action_to_schedule_ = move_action_;
  tick.status_ = 0;
  return tick;
}
