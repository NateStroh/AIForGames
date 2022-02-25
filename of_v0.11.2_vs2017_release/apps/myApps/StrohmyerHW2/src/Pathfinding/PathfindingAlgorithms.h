// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_PATHFINDING_PATHFINDINGALGORITHMS_H_
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_PATHFINDING_PATHFINDINGALGORITHMS_H_

#include "ConnectionGraph.h"

#include <vector>

namespace AI {

namespace PathfindingAlgorithms {
std::vector<int> DijkstraSearch(ConnectionGraph* graph, int num_elements,
                                int start_node, int end_node);

std::vector<int> AStarSearchMDH(ConnectionGraph* graph, int num_elements,
                             int start_node, int end_node);

std::vector<int> AStarSearchEDH(ConnectionGraph* graph, int num_elements,
                                int start_node, int end_node, float tile_size);

std::vector<int> AStarSearchRH(ConnectionGraph* graph, int num_elements,
                                int start_node, int end_node);

int ManhattanDistanceHueristic(int columns, int start_index, int end_index);

int EuclidianDistanceHueristic(int columns, int start_index, int end_index,
                               float tile_size);

int RandomHueristic(int low_value, int high_value);

}  // namespace PathfindingAlgorithms

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW2_SRC_PATHFINDING_PATHFINDINGALGORITHMS_H_
