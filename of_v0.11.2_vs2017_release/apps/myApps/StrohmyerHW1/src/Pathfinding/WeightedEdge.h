// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_PATHFINDING_WEIGHTEDEDGE_H_
#define STROHMYERHW1_SRC_PATHFINDING_WEIGHTEDEDGE_H_

namespace AI {

namespace PathfindingAlgorithms {

struct WeightedEdge {
  int from_node;
  int to_node;
  float cost; 

  bool WeightedEdge::operator==(const WeightedEdge other) {
    return (from_node == other.from_node && to_node == other.to_node &&
            cost == other.cost);
  }

  bool WeightedEdge::operator<(const WeightedEdge& other) const {
    return (cost > other.cost);
  }

};


}  // namespace PathfindingAlgorithms

}  // namespace AI

#endif  // STROHMYERHW1_SRC_PATHFINDING_WEIGHTEDEDGE_H_