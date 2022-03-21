// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_GOAP_GOAP
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_GOAP_GOAP

#include "../Actions/Action.h"
#include "Task.h"

namespace AI {

namespace DecisionMaking {

class GOAP {
 public:
  std::vector<Task> GetBestAction(std::vector<bool> start,
                        std::vector<bool> goal,
                        std::vector<Task> tasks);
  std::vector<bool> UpdateState(std::vector<bool> state, Task task);
  
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_GOAP_GOAP
