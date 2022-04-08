#include "AttackActionRight.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::AttackActionRight::Run(
    BTTick tick) {
  tick.action_to_schedule_ = attack_action_;
  tick.status_ = 0;
  return tick;
}