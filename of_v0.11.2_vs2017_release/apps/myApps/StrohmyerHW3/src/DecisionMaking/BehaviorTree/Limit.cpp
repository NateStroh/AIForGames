#include "Limit.h"

AI::DecisionMaking::BTTick AI::DecisionMaking::Limit::Run(BTTick tick) {
  if (runs_so_far >= run_limit_) {
    tick.status_ = 1;
    return tick;
  }

  runs_so_far++;
  return child_->Run(tick);
}

AI::DecisionMaking::Limit::Limit() : 
  run_limit_(0), runs_so_far(0) {}

AI::DecisionMaking::Limit::Limit(int run_limit) : 
  run_limit_(run_limit), runs_so_far(0) {}
