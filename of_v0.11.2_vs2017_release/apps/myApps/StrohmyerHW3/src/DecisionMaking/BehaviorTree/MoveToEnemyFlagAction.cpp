#include "MoveToEnemyFlagAction.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::MoveToEnemyFlagAction::Run(
    BTTick tick) {
  tick.action_to_schedule_ = move_action_;
  tick.status_ = 0;
  return tick;
}
