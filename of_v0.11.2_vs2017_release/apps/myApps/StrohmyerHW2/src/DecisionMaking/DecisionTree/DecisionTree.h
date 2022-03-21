// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREE
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREE

#include "../Actions/Action.h"
#include "../Actions/ActionManager.h"
#include "DecisionTreeNode.h"

namespace AI {

namespace DecisionMaking {

class DecisionTree {
 public:
  DecisionTreeNode* root_node_;
  ActionManager* action_manager_;
  std::vector<DecisionTreeNode> decision_tree_nodes_;

  bool MakeDecision();

  // make a connection node
  void ConnectNodes(int parent_node_index, int child_node_index, bool is_left_node);
}; 

}  // namespace DecisionMaking

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_DECISIONMAKING_DECISIONTREE_DECISIONTREE
