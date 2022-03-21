// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREENODE
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREENODE

namespace AI {

namespace DecisionMaking {

class DecisionTreeNode {
 public:
  virtual DecisionTreeNode* MakeDecision();

};

} // namespace DecisionMaking

} // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREENODE
