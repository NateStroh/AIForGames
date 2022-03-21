// copyright 2022 Nate Strohmyer

#include "GOAP.h"
#include <queue>
#include <map>

struct StateToCost {
  std::vector<bool> state;
  int cost;

  StateToCost(std::vector<bool> state_val, int cost_val)
      : state(state_val), cost(cost_val) {}

  bool StateToCost::operator<(const StateToCost& other) const {
    return (cost > other.cost);
  }
};

int HammingDistance(std::vector<bool> state_1, std::vector<bool> state_2) {
  return 10;
}

std::vector<AI::DecisionMaking::Task> AI::DecisionMaking::GOAP::GetBestAction(
    std::vector<bool> start,
    std::vector<bool> goal,
    std::vector<Task> tasks) {
  // start fringe - priority queue
  std::priority_queue<StateToCost> fringe;
  fringe.push(StateToCost(start, 0));
  std::map<std::vector<bool>, int> cost_so_far;
  std::map<Task, Task> came_from;
  // int* cost_so_far = new int[tasks.size()];
  // int* came_from = new int[tasks.size()];
  //for (unsigned int i = 0; i < tasks.size; i++) {
  //  cost_so_far[i] = INT_MAX;
  //}
  cost_so_far.insert(std::pair<std::vector<bool>, int>(start, 0));

  int nodes_explored = 0;

   std::vector<bool> current_state = start;
  // while fringe isn't empty
  while (!fringe.empty()) {
    // get element from fringe
    current_state = fringe.top().state;
    fringe.pop();

    // if we've reached the goal we can stop
    if (current_state == goal) break;

    int num_neighbors = graph->num_nodes;
    // else generate children and add unique items to fringe
    for (int i = 0; i < num_neighbors; i++) {
      // if it has a cost - 0 means no connection
      if (graph->data[current_state][i] != 0) {
        int new_cost = cost_so_far[current_state] +
                       graph->data[current_state][i] +
                       HammingDistance();

        if (new_cost < cost_so_far[i]) {
          cost_so_far[i] = new_cost;
          came_from[i] = current_state;
          fringe.push(StateToCost(i, new_cost));
          nodes_explored++;
        }
      }
    }
  }
  // if we haven't found goal we can't get there - return null
  if (current_state != goal) return std::vector<Task>();

  // assemble and return the correct path
  std::vector<Task> shortest_path;
  shortest_path.push_back();
  while (current_state != start_node_index) {
    shortest_path.push_back(came_from[current_state]);
    current_state = came_from[current_state];
  }

  printf("GOAP: explored %d nodes\n", nodes_explored);

  // delete[] cost_so_far;
  // delete[] came_from;

  std::reverse(shortest_path.begin(), shortest_path.end());
  return shortest_path;
}

std::vector<bool> AI::DecisionMaking::GOAP::UpdateState(std::vector<bool> state,
                                                        Task task) {
  std::vector<bool> return_state = state;
  // if conditions met  
  if ((return_state ^ task.pre_) == 0) {
    // delete conditions
    return_state = ((~task.del_) & return_state);
    // add conditions
    return_state = (task.add_ | return_state);
  }
  return state;
}
