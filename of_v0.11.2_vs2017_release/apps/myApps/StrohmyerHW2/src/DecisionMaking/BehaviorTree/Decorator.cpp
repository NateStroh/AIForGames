#include "Decorator.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::Decorator::Run(BTTick tick) {
  return child_.Run(tick);
}
