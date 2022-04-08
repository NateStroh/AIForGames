// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionCombination
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionCombination

#include "Action.h"
#include <Vector>

namespace AI {

namespace DecisionMaking {

class ActionCombination : public AI::DecisionMaking::Action {
 public:
  std::vector<Action> actions;

  bool AI::DecisionMaking::ActionCombination::CanInterupt();
  bool AI::DecisionMaking::ActionCombination::CanDoBoth(Action const &other);
  bool AI::DecisionMaking::ActionCombination::IsComplete();
  int AI::DecisionMaking::ActionCombination::Execute();
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionCombination