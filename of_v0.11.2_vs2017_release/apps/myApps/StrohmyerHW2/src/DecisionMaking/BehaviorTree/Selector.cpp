#include "Selector.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::Selector::Run(BTTick tick) {
  BTTick newTick;
  for (size_t i = 0; i < children_.size(); i++) {
    newTick = children_[i].Run(tick);
    if (newTick.status_ == 0) {
      return newTick;
    }
  }
  return newTick;
}
