#pragma once

#include "..\DecisionTreeDecision.h"

#include "..\..\..\GameObjects\Boid.h"

namespace AI {

namespace DecisionMaking {

class EnemyInRangeDecision : public AI::DecisionMaking::DecisionTreeDecision {
 public:
  Boid* boid_;
  Boid* enemy_boid_;
  float range_;

  EnemyInRangeDecision();
  EnemyInRangeDecision(Boid* boid, Boid* enemy_boid, float range = 50);
  EnemyInRangeDecision(Boid* boid, Boid* enemy_boid,
                       DecisionTreeNode* left_node,
                       DecisionTreeNode* right_node, float range = 50);
  DecisionTreeNode* GetBranch();
};

}  // namespace DecisionMaking

}  // namespace AI
