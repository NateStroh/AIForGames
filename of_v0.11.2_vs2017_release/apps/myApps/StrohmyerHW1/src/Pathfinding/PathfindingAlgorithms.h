// copyright 2022 Nate Strohmyer

#ifndef STROHMYERHW1_SRC_PATHFINDING_PATHFINDINGALGORITHMS_H_
#define STROHMYERHW1_SRC_PATHFINDING_PATHFINDINGALGORITHMS_H_

#include "WeightedEdge.h"
#include "ConnectionGraph.h"

#include <vector>

namespace AI {

namespace PathfindingAlgorithms {
std::vector<int> DijkstraSearch(ConnectionGraph* graph, int num_elements,
                                int start_node, int end_node);

std::vector<int> AStarSearch(ConnectionGraph* graph, int num_elements,
                             int start_node, int end_node);

int ManhattanDistanceHueristic(int columns,
                               int start_index, 
                               int end_index);

int RandomHueristic(int low_value, int high_value);

}  // namespace PathfindingAlgorithms

}  // namespace AI

#endif  // STROHMYERHW1_SRC_PATHFINDING_PATHFINDINGALGORITHMS_H_
