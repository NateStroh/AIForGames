#include "BehaviorTree.h"

#include "BTTick.h"

AI::DecisionMaking::Action* AI::DecisionMaking::BehaviorTree::GetAction() {
  BTTick newTick;
  newTick.black_board_pointer_ = &blackboard_;
  
  BTTick tick = root_node_->Run(newTick);
  switch (tick.status_) {
    // 0 = success
    case 0:
      action_manager_->ScheduleAction(tick.action_to_schedule_);
      return tick.action_to_schedule_;
      break;
    // 1 = fail 
    case 1:
      return nullptr;
      break;
    // 2 = running
    case 2:
      return nullptr;
      break;
    // 3 = error
    case 3:
      return nullptr;
      break;
    default:
      return nullptr;
      break;
  }
}
