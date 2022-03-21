// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREEDECISION
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREEDECISION

#include "DecisionTreeNode.h"

namespace AI {

namespace DecisionMaking {

class DecisionTreeDecision : public DecisionTreeNode {
 public:
  DecisionTreeNode* true_node_;
  DecisionTreeNode* false_node_;

  virtual DecisionTreeNode* GetBranch();
  DecisionTreeNode* MakeDecision();
};

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREEDECISION
