#include "HaveEnemyFlagCondition.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::HaveEnemyFlagCondition::Run(
    BTTick tick) {
  if (*flag_taken_) {
    tick.status_ = 0;
  } else {
    tick.status_ = 1;
  }

  return tick;
}
