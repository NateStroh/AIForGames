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

struct GOAPNode {
  AI::DecisionMaking::Task task;
  std::vector<bool> state;

  GOAPNode(AI::DecisionMaking::Task task_val, std::vector<bool> state_val) {
    task = task_val;
    state = state_val;
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
  std::map<std::vector<bool>, GOAPNode> came_from;
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

    int num_neighbors = tasks.size();
    // else generate children and add unique items to fringe
    for (int i = 0; i < num_neighbors; i++) {
      std::vector<bool> new_state = UpdateState(current_state, tasks[i]);

      // try to find the items cost so far
      auto itr = cost_so_far.find(current_state);
      int current_cost;
      if (itr == cost_so_far.end()) {
        current_cost = 0;
      } else {
        current_cost = itr->second;
      }

      int new_cost = current_cost +
                     HammingDistance(current_state, new_state);

      if (new_cost < current_cost) {
        cost_so_far.insert({new_state, new_cost});
        came_from.insert({new_state, GOAPNode(tasks[i], current_state)});
        fringe.push(StateToCost(new_state, new_cost));
        nodes_explored++;
      }
    }
  }
  // if we haven't found goal we can't get there - return null
  if (current_state != goal) return std::vector<Task>();

  // assemble and return the correct path
  std::vector<Task> shortest_path;

  // try to find the item
  auto itr = came_from.find(goal);
  if (itr == came_from.end()) {
    printf("THIS SHOULD NOT HAPPEN - DIDN't FIND A GOAL\n");
    return std::vector<Task>();
  } else {
    shortest_path.push_back(itr->second.task);
  }

  while (current_state != start) {
    // try to find the item
    auto itr = came_from.find(current_state);
    if (itr == came_from.end()) {
      printf("THIS SHOULD NOT HAPPEN - DIDN'T FIND A STATE\n");
      return std::vector<Task>();
    } else {
      shortest_path.push_back(itr->second.task);
      current_state = itr->first;
    }
  }

  printf("GOAP: explored %d nodes\n", nodes_explored);

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
