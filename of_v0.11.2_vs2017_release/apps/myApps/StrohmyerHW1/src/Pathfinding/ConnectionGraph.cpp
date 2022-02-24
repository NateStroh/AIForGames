// copyright 2022 Nate Strohmyer
#include "ConnectionGraph.h"

AI::PathfindingAlgorithms::ConnectionGraph::ConnectionGraph() {
  rows = 0;
  columns = 0;
  num_nodes = 0;
  data = new uint8_t*[1];
  for (unsigned int i = 0; i < 1; i++) {
    data[i] = new uint8_t[1];
  }
}

AI::PathfindingAlgorithms::ConnectionGraph::ConnectionGraph(
    unsigned int rows_input, unsigned int columns_input) {
  rows = rows_input;
  columns = columns_input;
  num_nodes = rows * columns;
  data = new uint8_t*[num_nodes];
  for (unsigned int i = 0; i < num_nodes; i++) {
    data[i] = new uint8_t[num_nodes];
  }

  for (unsigned int i = 0; i < num_nodes; i++) {
    for (unsigned int j = 0; j < num_nodes; j++) {
      data[i][j] = 0;
    }
  }
}

AI::PathfindingAlgorithms::ConnectionGraph::ConnectionGraph(
    unsigned int rows_input, unsigned int columns_input,
                unsigned int default_value) {
  rows = rows_input;
  columns = columns_input;
  num_nodes = rows * columns;
  data = new uint8_t*[num_nodes];
  for (int unsigned i = 0; i < num_nodes; i++) {
    data[i] = new uint8_t[num_nodes];
  }

  for (unsigned int i = 0; i < num_nodes; i++) {
    for (unsigned int j = 0; j < num_nodes; j++) {
      data[i][j] = default_value;
    }
  }
}

AI::PathfindingAlgorithms::ConnectionGraph::ConnectionGraph(
    const ConnectionGraph& other)
    : num_nodes(other.num_nodes), rows(other.rows), columns(other.columns) {
  data = new uint8_t*[num_nodes];
  for (unsigned int i = 0; i < num_nodes; i++) {
    data[i] = new uint8_t[num_nodes];
  }

  for (unsigned int i = 0; i < num_nodes; i++) {
    for (unsigned int j = 0; j < num_nodes; j++) {
      data[i][j] = other.data[i][j];
    }
  }
}

AI::PathfindingAlgorithms::ConnectionGraph&
    AI::PathfindingAlgorithms::ConnectionGraph::operator=(
    const ConnectionGraph& other) {
  if (this != &other) {
    for (unsigned int i = 0; i < num_nodes; i++) delete[] data[i];
    delete[] data;

    rows = other.rows;
    columns = other.columns;
    num_nodes = other.num_nodes;
    data = new uint8_t*[num_nodes];
    for (unsigned int i = 0; i < num_nodes; i++) {
      data[i] = new uint8_t[num_nodes];
    }

    for (unsigned int i = 0; i < num_nodes; i++) {
      for (unsigned int j = 0; j < num_nodes; j++) {
        data[i][j] = other.data[i][j];
      }
    }
  }
  return *this;
}

AI::PathfindingAlgorithms::ConnectionGraph::~ConnectionGraph() {
  for (unsigned int i = 0; i < num_nodes; i++) delete[] data[i];
  delete[] data;
}
