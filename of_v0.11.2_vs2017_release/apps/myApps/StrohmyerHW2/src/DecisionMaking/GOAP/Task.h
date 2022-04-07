// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_GOAP_TASK
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_GOAP_TASK

#include "../Actions/Action.h"
#include <vector>

namespace AI {

namespace DecisionMaking {

class Task {
 public:
  std::vector<bool> pre_;
  std::vector<bool> add_;
  std::vector<bool> del_;
  Action* action_to_schedule;

  Task();
  Task(Action* action);
  ~Task();
};

} // namespace DecisionMaking

} // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_GOAP_TASK
