#include "s21_graph_algorithms.h"

#include <_types/_uint32_t.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "container_adaptors/s21_queue.h"
#include "container_adaptors/s21_stack.h"

namespace s21 {
using std::vector;

vector<uint32_t> GraphAlgorithms::DepthFirstSearch(const Graph &graph,
                                                   uint32_t start_vertex) {
  if (start_vertex == 0 || start_vertex > graph.GetSize()) {
    throw std::out_of_range("Invalid values for start vertex");
  }
  matrix_uint32_t matrix = graph.GetMatrix();
  vector<uint32_t> result;
  vector<bool> visited(graph.GetSize() + 1, false);
  stack<uint32_t> stack;
  stack.push(start_vertex);

  while (stack.empty() == false) {
    uint32_t current_vertex = stack.top();
    stack.pop();

    if (visited[current_vertex] == false) {
      result.push_back(current_vertex);
      visited[current_vertex] = true;
    }

    for (int64_t i = graph.GetSize() - 1; i >= 0; --i) {
      if ((matrix[current_vertex - 1][i] > 0) && (!visited[i + 1])) {
        stack.push(i + 1);
      }
    }
  }

  return result;
}

vector<uint32_t> GraphAlgorithms::BreadthFitstSearch(const Graph &graph,
                                                     uint32_t start_vertex) {
  if (start_vertex == 0 || start_vertex > graph.GetSize()) {
    throw std::out_of_range("Invalid values for start vertex");
  }
  matrix_uint32_t matrix = graph.GetMatrix();
  vector<uint32_t> result;
  vector<bool> visited(graph.GetSize(), false);
  queue<uint32_t> queue;
  queue.push(start_vertex);

  while (queue.empty() == false) {
    uint32_t current_vertex = queue.front();
    queue.pop();

    if (visited[current_vertex] == false) {
      result.push_back(current_vertex);
      visited[current_vertex] = true;
    }

    for (size_t i = 0; i < graph.GetSize(); ++i) {
      if ((matrix[current_vertex - 1][i] > 0) && (!visited[i + 1])) {
        queue.push(i + 1);
      }
    }
  }

  return result;
}

size_t GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                       uint32_t from,
                                                       uint32_t to) {
  if (from > graph.GetSize() || to > graph.GetSize() || from == 0 ||
      to < from) {
    throw std::out_of_range("Invalid values for vertexes");
  } else if (from == to) {
    return graph.GetMatrix()[from - 1][to - 1];
  }

  matrix_uint32_t adjacency_matrix = graph.GetMatrix();
  size_t size = graph.GetSize();
  AdjacencyMatrixPrepare(adjacency_matrix, graph.GetSize());

  vector<size_t> minimum_distance(size, kMax);
  minimum_distance[from - 1] = 0;

  vector<bool> visit(size);
  size_t min_dist = 0;
  int min_vertex = from - 1;

  while (min_dist < kMax) {
    int i = min_vertex;
    visit[i] = true;
    for (size_t j = 0; j < size; ++j) {
      if (minimum_distance[i] + adjacency_matrix[i][j] < minimum_distance[j])
        minimum_distance[j] = minimum_distance[i] + adjacency_matrix[i][j];
    }
    min_dist = kMax;

    for (size_t j = 0; j < size; ++j) {
      if (!visit[j] && minimum_distance[j] < min_dist) {
        min_dist = minimum_distance[j];
        min_vertex = j;
      }
    }
  }
  return minimum_distance[to - 1];
}

GraphAlgorithms::matrix_uint32_t
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  size_t size = graph.GetSize();
  matrix_uint32_t matrix = graph.GetMatrix();
  AdjacencyMatrixPrepare(matrix, graph.GetSize());
  for (size_t k = 0; k < size; k++) {
    for (size_t i = 0; i < size; i++) {
      for (size_t j = 0; j < size; j++) {
        if (matrix[i][j] > (matrix[i][k] + matrix[k][j]) &&
            matrix[k][j] != kMax && matrix[i][k] != kMax) {
          matrix[i][j] = matrix[i][k] + matrix[k][j];
        }
      }
    }
  }
  for (size_t row = 0; row < size; ++row) {
    for (size_t col = 0; col < size; ++col) {
      if (matrix[row][col] == kMax || row == col) {
        matrix[row][col] = 0;
      }
    }
  }
  return matrix;
}

void GraphAlgorithms::AdjacencyMatrixPrepare(matrix_uint32_t &adjacency_matrix,
                                             size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (adjacency_matrix[i][j] == 0) {
        adjacency_matrix[i][j] = kMax;
      }
    }
  }
}

GraphAlgorithms::matrix_uint32_t GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  size_t size = graph.GetSize();
  matrix_uint32_t matrix = graph.GetMatrix();
  matrix_uint32_t matrix_res(size, std::vector<uint32_t>(size));
  AdjacencyMatrixPrepare(matrix, size);

  size_t no_edge = 0;
  int selected[size];
  memset(selected, false, sizeof(selected));
  selected[0] = true;

  size_t x, y;
  while (no_edge < size - 1) {
    size_t min = kMax;
    x = 0;
    y = 0;

    for (size_t i = 0; i < size; i++) {
      if (selected[i]) {
        for (size_t j = 0; j < size; j++) {
          if (!selected[j] && matrix[i][j]) {
            if (min > matrix[i][j]) {
              min = matrix[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    matrix_res[x][y] = matrix[x][y];
    selected[y] = true;
    no_edge++;
  }
  return matrix_res;
}

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph &graph) {
  AntColony colony(graph);
  return colony.SolveSalesmansProblem();
}
}  // namespace s21
