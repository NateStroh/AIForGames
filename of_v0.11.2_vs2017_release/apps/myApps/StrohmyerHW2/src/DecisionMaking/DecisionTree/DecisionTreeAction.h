// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREEACTION
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREEACTION

#include "../Actions/Action.h"
#include "DecisionTreeNode.h"

namespace AI {

namespace DecisionMaking {

class DecisionTreeAction : public DecisionTreeNode {
 public:
  Action* action;

  DecisionTreeNode* MakeDecision();

  DecisionTreeAction();
  DecisionTreeAction(Action action_to_add);
  ~DecisionTreeAction();
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREEACTION
