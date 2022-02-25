// copyright 2022 Nate Strohmyer
#include "PathfindingAlgorithms.h"

#include <time.h>

#include <random>
#include <queue>

#include "ofVec2f.h"

struct IndexToCost {
  int index;
  int cost;

  IndexToCost() : index(0), cost(0) {}
  IndexToCost(int index_val, int cost_val) : index(index_val), cost(cost_val) {}

  bool IndexToCost::operator<(const IndexToCost& other) const {
    return (cost > other.cost);
  }
};

std::vector<int> AI::PathfindingAlgorithms::DijkstraSearch(
    ConnectionGraph* graph, int num_elements, int start_node_index,
    int end_node_index) {
  // start fringe - priority queue
  std::priority_queue<IndexToCost> fringe;
  fringe.push(IndexToCost(start_node_index, 0));
  int* cost_so_far = new int[num_elements];
  int* came_from = new int[num_elements];
  for (int i = 0; i < num_elements; i++) {
    cost_so_far[i] = INT_MAX;
  }
  cost_so_far[start_node_index] = 0;

  int nodes_explored = 0;

  int current_node = 0;
  // while fringe isn't empty
  while (!fringe.empty()) {
    // get element from fringe
    current_node = fringe.top().index;
    fringe.pop();

    // if we've reached the goal we can stop
    if (current_node == end_node_index) break;

    int num_neighbors = num_elements;
    // else generate children and add unique items to fringe
    for (int i = 0; i < num_neighbors; i++) {
      // if it has a cost - 0 means no connection
      if (graph->data[current_node][i] != 0) {
        int new_cost = cost_so_far[current_node] + graph->data[current_node][i];

        if (new_cost < cost_so_far[i]) {
          cost_so_far[i] = new_cost;
          came_from[i] = current_node;
          fringe.push(IndexToCost(i, new_cost));
          nodes_explored++;
        }
      }
    }
  }
  // if we haven't found goal we can't get there - return null
  if (current_node != end_node_index) return std::vector<int>();

  // assemble and return the correct path
  std::vector<int> shortest_path;
  shortest_path.push_back(end_node_index);
  while (current_node != start_node_index) {
    shortest_path.push_back(came_from[current_node]);
    current_node = came_from[current_node];
  }

  printf("Dijkstra's: explored %d nodes\n", nodes_explored);

  delete[] cost_so_far;
  delete[] came_from;

  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

std::vector<int> AI::PathfindingAlgorithms::AStarSearchMDH(
    ConnectionGraph* graph,
    int num_elements,
    int start_node_index,
    int end_node_index) {
  // start fringe - priority queue
  std::priority_queue<IndexToCost> fringe;
  fringe.push(IndexToCost(start_node_index, 0));
  int* cost_so_far = new int[graph->num_nodes];
  int* came_from = new int[graph->num_nodes];
  for (unsigned int i = 0; i < graph->num_nodes; i++) {
    cost_so_far[i] = INT_MAX;
  }
  cost_so_far[start_node_index] = 0;

  int nodes_explored = 0;

  int current_node = 0;
  // while fringe isn't empty
  while (!fringe.empty()) {
    // get element from fringe
    current_node = fringe.top().index;
    fringe.pop();

    // if we've reached the goal we can stop
    if (current_node == end_node_index) break;

    int num_neighbors = graph->num_nodes;
    // else generate children and add unique items to fringe
    for (int i = 0; i < num_neighbors; i++) {
      // if it has a cost - 0 means no connection
      if (graph->data[current_node][i] != 0) {
        int new_cost = cost_so_far[current_node] + graph->data[current_node][i]
            + ManhattanDistanceHueristic(graph->columns,
                                         current_node,
                                         end_node_index);

        if (new_cost < cost_so_far[i]) {
          cost_so_far[i] = new_cost;
          came_from[i] = current_node;
          fringe.push(IndexToCost(i, new_cost));
          nodes_explored++;
        }
      }
    }
  }
  // if we haven't found goal we can't get there - return null
  if (current_node != end_node_index) return std::vector<int>();

  // assemble and return the correct path
  std::vector<int> shortest_path;
  shortest_path.push_back(end_node_index);
  while (current_node != start_node_index) {
    shortest_path.push_back(came_from[current_node]);
    current_node = came_from[current_node];
  }

  printf("AStarMDH: explored %d nodes\n", nodes_explored);

  delete[] cost_so_far;
  delete[] came_from;

  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

std::vector<int> AI::PathfindingAlgorithms::AStarSearchEDH(
    ConnectionGraph* graph, int num_elements, int start_node, int end_node,
    float tile_size) {
  // start fringe - priority queue
  std::priority_queue<IndexToCost> fringe;
  fringe.push(IndexToCost(start_node, 0));
  int* cost_so_far = new int[graph->num_nodes];
  int* came_from = new int[graph->num_nodes];
  for (unsigned int i = 0; i < graph->num_nodes; i++) {
    cost_so_far[i] = INT_MAX;
  }
  cost_so_far[start_node] = 0;

  int nodes_explored = 0;

  int current_node = 0;
  // while fringe isn't empty
  while (!fringe.empty()) {
    // get element from fringe
    current_node = fringe.top().index;
    fringe.pop();

    // if we've reached the goal we can stop
    if (current_node == end_node) break;

    int num_neighbors = graph->num_nodes;
    // else generate children and add unique items to fringe
    for (int i = 0; i < num_neighbors; i++) {
      // if it has a cost - 0 means no connection
      if (graph->data[current_node][i] != 0) {
        int new_cost = cost_so_far[current_node] +
                       graph->data[current_node][i] +
                       EuclidianDistanceHueristic(graph->columns, current_node,
                                                  end_node, tile_size);

        if (new_cost < cost_so_far[i]) {
          cost_so_far[i] = new_cost;
          came_from[i] = current_node;
          fringe.push(IndexToCost(i, new_cost));
          nodes_explored++;
        }
      }
    }
  }
  // if we haven't found goal we can't get there - return null
  if (current_node != end_node) return std::vector<int>();

  // assemble and return the correct path
  std::vector<int> shortest_path;
  shortest_path.push_back(end_node);
  while (current_node != start_node) {
    shortest_path.push_back(came_from[current_node]);
    current_node = came_from[current_node];
  }

  printf("AStarEDH: explored %d nodes\n", nodes_explored);

  delete[] cost_so_far;
  delete[] came_from;

  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

std::vector<int> AI::PathfindingAlgorithms::AStarSearchRH(
    ConnectionGraph* graph, int num_elements, int start_node, int end_node) {
  // start fringe - priority queue
  std::priority_queue<IndexToCost> fringe;
  fringe.push(IndexToCost(start_node, 0));
  int* cost_so_far = new int[graph->num_nodes];
  int* came_from = new int[graph->num_nodes];
  for (unsigned int i = 0; i < graph->num_nodes; i++) {
    cost_so_far[i] = INT_MAX;
  }
  cost_so_far[start_node] = 0;

  int nodes_explored = 0;

  int current_node = 0;
  // while fringe isn't empty
  while (!fringe.empty()) {
    // get element from fringe
    current_node = fringe.top().index;
    fringe.pop();

    // if we've reached the goal we can stop
    if (current_node == end_node) break;

    int num_neighbors = graph->num_nodes;
    // else generate children and add unique items to fringe
    for (int i = 0; i < num_neighbors; i++) {
      // if it has a cost - 0 means no connection
      if (graph->data[current_node][i] != 0) {
        int new_cost = cost_so_far[current_node] +
                       graph->data[current_node][i] +
                       RandomHueristic(1, 10);

        if (new_cost < cost_so_far[i]) {
          cost_so_far[i] = new_cost;
          came_from[i] = current_node;
          fringe.push(IndexToCost(i, new_cost));
          nodes_explored++;
        }
      }
    }
  }
  // if we haven't found goal we can't get there - return null
  if (current_node != end_node) return std::vector<int>();

  // assemble and return the correct path
  std::vector<int> shortest_path;
  shortest_path.push_back(end_node);
  while (current_node != start_node) {
    shortest_path.push_back(came_from[current_node]);
    current_node = came_from[current_node];
  }

  printf("AStarRH: explored %d nodes\n", nodes_explored);

  delete[] cost_so_far;
  delete[] came_from;

  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

int AI::PathfindingAlgorithms::ManhattanDistanceHueristic(int columns,
                                                          int start_index,
                                                          int end_index) {
  int start_index_x = start_index / columns;
  int start_index_y = start_index % columns;
  int end_index_x = end_index / columns;
  int end_index_y = end_index % columns;

  return (abs(start_index_x - end_index_x) + abs(start_index_y - end_index_y));
}

int AI::PathfindingAlgorithms::EuclidianDistanceHueristic(int columns,
                                                          int start_index,
                                                          int end_index,
                                                          float tile_size) {
  int start_index_x = start_index / columns;
  int start_index_y = start_index % columns;
  int end_index_x = end_index / columns;
  int end_index_y = end_index % columns;
  ofVec2f position_1;
  position_1.x = start_index_y * tile_size + tile_size / 2;
  position_1.y = start_index_x * tile_size + tile_size / 2;
  ofVec2f position_2;
  position_2.x = end_index_y * tile_size + tile_size / 2;
  position_2.y = end_index_x * tile_size + tile_size / 2;

  float a = (position_1.x - position_2.x);
  float b = (position_1.y - position_2.y);
  return (sqrt((a*a) + (b*b)));
}

int AI::PathfindingAlgorithms::RandomHueristic(int low_value, int high_value) {
  srand(time(NULL));
  return (low_value + rand() % (high_value - low_value));
}
