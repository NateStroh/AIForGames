// copyright 2022 Nate Strohmyer

#ifndef OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW1_SRC_PATHFINDING_CONNECTIONGRAPH_H_
#define OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW1_SRC_PATHFINDING_CONNECTIONGRAPH_H_

#include <vector>

namespace AI {

namespace PathfindingAlgorithms {

struct ConnectionGraph {
  unsigned int num_nodes;
  unsigned int rows;
  unsigned int columns;
  uint8_t** data;

  ConnectionGraph();

  ConnectionGraph(unsigned int rows_input, unsigned int columns_input);

  ConnectionGraph(unsigned int rows_input,
                  unsigned int columns_input,
                  unsigned int default_value);

  ConnectionGraph(const ConnectionGraph& other);

  ConnectionGraph& operator=(const ConnectionGraph& other);

  ~ConnectionGraph();
};

}  // namespace PathfindingAlgorithms

}  // namespace AI

#endif  // OF_V0_11_2_VS2017_RELEASE_APPS_MYAPPS_STROHMYERHW1_SRC_PATHFINDING_CONNECTIONGRAPH_H_
