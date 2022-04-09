#include "EnemyInRangeDecision.h"

AI::DecisionMaking::EnemyInRangeDecision::EnemyInRangeDecision() {
  Boid* boid_ = nullptr;
  Boid* enemy_boid_ = nullptr;
  float range_ = 0;
  false_node_ = nullptr;
  true_node_ = nullptr;
}

AI::DecisionMaking::EnemyInRangeDecision::EnemyInRangeDecision(Boid* boid,
                                                               Boid* enemy_boid,
                                                               float range) {
  Boid* boid_ = boid;
  Boid* enemy_boid_ = enemy_boid;
  float range_ = range;
  false_node_ = nullptr;
  true_node_ = nullptr;
}

AI::DecisionMaking::EnemyInRangeDecision::EnemyInRangeDecision(
    Boid* boid, Boid* enemy_boid, DecisionTreeNode* left_node,
    DecisionTreeNode* right_node, float range) {
  Boid* boid_ = boid;
  Boid* enemy_boid_ = enemy_boid;
  float range_ = range;
  false_node_ = left_node;
  true_node_ = right_node;
}

AI::DecisionMaking::DecisionTreeNode*
    AI::DecisionMaking::EnemyInRangeDecision::GetBranch() {
  ofVec2f direction = (enemy_boid_->rigidbody.position - boid_->rigidbody.position);
  float distance = direction.length();

  if (distance <= range_) {
    return true_node_;
  }
  return false_node_;
}
