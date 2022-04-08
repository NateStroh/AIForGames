// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_BTTICK
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_BTTICK

#include "../Actions/Action.h"
#include <map>

namespace AI {

namespace DecisionMaking {

struct BTTick {
  std::map<std::string, std::string>* black_board_pointer_;
  Action* action_to_schedule_;
  // 0 = success
  // 1 = fail
  // 2 = running
  // 3 = error
  int status_;
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_BTTICK