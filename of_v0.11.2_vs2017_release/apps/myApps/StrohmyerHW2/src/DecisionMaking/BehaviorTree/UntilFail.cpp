#include "Decorator.h"
#include "UntilFail.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::UntilFail::Run(BTTick tick) {
  BTTick new_tick;
  while (true) {
    new_tick = child_.Run(tick);
    if (new_tick.status_ == 1 || new_tick.status_ == 3) {
      break;
    }
  }

  return new_tick;
}
