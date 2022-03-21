// copyright 2022 Nate Strohmyer

#include "ActionManager.h"
#include "ofUtils.h"
#include<algorithm> // for heap 

AI::DecisionMaking::ActionManager::ActionManager() {
  std::make_heap(queued_actions_.begin(), queued_actions_.end());
  std::make_heap(active_actions_.begin(), active_actions_.end());
}

void AI::DecisionMaking::ActionManager::ScheduleAction(Action* action) {
  queued_actions_.push_back(action);
  std::push_heap(queued_actions_.begin(), queued_actions_.end());
}

void AI::DecisionMaking::ActionManager::Execute() {
  uint64_t current_time = ofGetCurrentTime().getAsMilliseconds();
  int priority_cutoff = 0;
  if (!active_actions_.empty()) {
    priority_cutoff = active_actions_.front()->priority_;
  }

  // remove expired items from queue
  for (size_t i=0; i<queued_actions_.size(); i++) {
    if (queued_actions_[i]->expiry_time_ < current_time) {
      queued_actions_.erase(queued_actions_.begin()+i);
    }
  }
  std::make_heap(queued_actions_.begin(), queued_actions_.end());

  // loop trough queue
  for (size_t i = 0; i < queued_actions_.size(); i++) {
    if (queued_actions_[i]->priority_ <= priority_cutoff)
      break;
    
    // check for interupts
    if (queued_actions_[i]->CanInterupt()) {
      // clear the current active actions - this should be the only thing running
      active_actions_.clear();
      // add new action to active actions
      active_actions_.push_back(queued_actions_[i]);
      std::push_heap(active_actions_.begin(), active_actions_.end());
      
      // remove it from the queue
      queued_actions_.erase(queued_actions_.begin() + i);
      std::make_heap(queued_actions_.begin(), queued_actions_.end());
    } else {
      if (active_actions_.empty()) {
        // add new action to active actions
        active_actions_.push_back(queued_actions_.front());
        std::push_heap(active_actions_.begin(), active_actions_.end());

        // remove it from the queue
        queued_actions_.erase(queued_actions_.begin());
        std::make_heap(queued_actions_.begin(), queued_actions_.end());
      }
      // check for tasks that can run at the same time
      for (size_t j = 0; j < active_actions_.size(); j++) {
        if (!queued_actions_.empty()) {
          if (active_actions_[j]->CanDoBoth(*(queued_actions_[i]))) {
            // add new action to active actions
            active_actions_.push_back(queued_actions_[i]);
            std::push_heap(active_actions_.begin(), active_actions_.end());

            // remove it from the queue
            queued_actions_.erase(queued_actions_.begin() + i);
            std::make_heap(queued_actions_.begin(), queued_actions_.end());
          }
        }
      }
    }
  }

  // execute actions from active actions heap
  for (size_t i = 0; i < active_actions_.size(); i++) {
    int status = 0;
    // if action is complete - remove it from active actions
    if (active_actions_[i]->IsComplete()) {
      active_actions_.erase(active_actions_.begin()+i);
      std::make_heap(active_actions_.begin(), active_actions_.end());
    } else {
      status = active_actions_[i]->Execute();
    }
    if (status != 0) {
      printf("Something went wrong: Action %d Status: %d\n", i, status);
    }
  }
}
