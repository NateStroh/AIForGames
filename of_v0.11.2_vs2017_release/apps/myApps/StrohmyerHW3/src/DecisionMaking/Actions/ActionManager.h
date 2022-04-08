// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionManager
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionManager

#include "Action.h"
#include<vector>

namespace AI {

namespace DecisionMaking {

class ActionManager {
 public:
  ActionManager();

  std::vector<Action*> queued_actions_;
  std::vector<Action*> active_actions_;

  void ScheduleAction(Action* action);
  void Execute();
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionManager
