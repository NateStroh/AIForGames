// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_UNTILFAIL
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_UNTILFAIL

#include "Decorator.h"

namespace AI {

namespace DecisionMaking {

class Limit : public Decorator {
 public:
  int run_limit_;

  Limit();
  Limit(int run_limit);
  BTTick Run(BTTick tick);
 private:
  int runs_so_far = 0;
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_UNTILFAIL