// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionSequence
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionSequence

#include "Action.h"
#include <Vector>

namespace AI {

namespace DecisionMaking {

class ActionSequence : public AI::DecisionMaking::Action {
 public:
  std::vector<Action> actions;
  int active_action_index;

  bool AI::DecisionMaking::ActionSequence::CanInterupt();
  bool AI::DecisionMaking::ActionSequence::CanDoBoth(Action other);
  bool AI::DecisionMaking::ActionSequence::IsComplete();
  int AI::DecisionMaking::ActionSequence::Execute();
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DecisionMaking_Actions_ActionSequence