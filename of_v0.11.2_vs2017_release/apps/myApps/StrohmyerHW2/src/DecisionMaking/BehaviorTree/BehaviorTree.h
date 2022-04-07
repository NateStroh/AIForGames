// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_BEHAVIORTREE
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_BEHAVIORTREE

#include "BehaviorTreeNode.h"

namespace AI {

namespace DecisionMaking {

class BehaviorTree {
 public:
  BehaviorTreeNode root_node_;

  Action* GetAction();
 private: 
  std::map<std::string, std::string> blackboard_;
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_BEHAVIORTREE_BEHAVIORTREE