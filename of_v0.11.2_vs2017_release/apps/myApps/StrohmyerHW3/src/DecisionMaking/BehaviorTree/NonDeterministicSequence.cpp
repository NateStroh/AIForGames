#include "NonDeterministicSequence.h"

#include <algorithm>

AI::DecisionMaking::BTTick AI::DecisionMaking::NonDetermenisticSequence::Run(
    BTTick tick) {
  std::vector<BehaviorTreeNode*> shuffled = children_;
  std::random_shuffle(shuffled.begin(), shuffled.end());

  BTTick newTick;
  for (size_t i = 0; i < shuffled.size(); i++) {
    newTick = shuffled[i]->Run(tick);
    if (newTick.status_ != 0) {
      return newTick;
    }
  }
  return newTick;

}
