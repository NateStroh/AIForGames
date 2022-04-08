#include "Sequencer.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::Sequencer::Run(BTTick tick) {
  BTTick newTick;
  for (size_t i = 0; i < children_.size(); i++) {
    newTick = children_[i]->Run(tick);
    if (newTick.status_ != 0) {
      return newTick;
    }
  }
  return newTick;
}
