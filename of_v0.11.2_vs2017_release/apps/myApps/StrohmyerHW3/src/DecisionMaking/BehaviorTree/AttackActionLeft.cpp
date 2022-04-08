#include "AttackActionLeft.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::AttackActionLeft::Run(
    BTTick tick) {
  tick.action_to_schedule_ = attack_action_;
  tick.status_ = 0;
  return tick;
}
