// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_MOVETOENEMYACTION
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_MOVETOENEMYACTION

#include "BehaviorTreeNode.h"

namespace AI {

namespace DecisionMaking {

class MoveToEnemyAction : public BehaviorTreeNode {
 public:
  Action* move_action_;

  BTTick Run(BTTick tick);
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_MOVETOENEMYACTION
