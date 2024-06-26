#include "s21_graph_algorithms.h"
#include "container_adaptors/s21_queue.h"
#include "container_adaptors/s21_stack.h"
#include <_types/_uint32_t.h>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace s21 {
using std::vector;

vector<uint32_t> GraphAlgorithms::DepthFirstSearch(const Graph &graph,
                                                   uint32_t start_vertex) {
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

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, size_t from,
                                                    size_t to) {
  if (from > graph.GetSize() || to > graph.GetSize()) {
    throw std::out_of_range("Invalid values for vertexes");
  } else if (from == to) {
    return graph.GetMatrix()[from - 1][to - 1];
  }

  matrix_uint32_t adjacency_matrix = graph.GetMatrix();
  size_t size = graph.GetSize();
  AdjacencyMatrixPrepare(adjacency_matrix, graph.GetSize());

  vector<size_t> minimum_distance(size, INF);
  minimum_distance[from - 1] = 0;

  vector<bool> visit(size);
  size_t min_dist = 0;
  int min_vertex = from - 1;

  while (min_dist < INF) {
    int i = min_vertex;
    visit[i] = true;
    for (size_t j = 0; j < size; ++j) {
      if (minimum_distance[i] + adjacency_matrix[i][j] < minimum_distance[j])
        minimum_distance[j] = minimum_distance[i] + adjacency_matrix[i][j];
    }
    min_dist = INF;

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
  matrix_uint32_t matrix = graph.GetMatrix();
  AdjacencyMatrixPrepare(matrix, graph.GetSize());
  for (size_t k = 0; k < graph.GetSize(); k++) {
    for (size_t i = 0; i < graph.GetSize(); i++) {
      for (size_t j = 0; j < graph.GetSize(); j++) {
        matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
  return matrix;
}

void GraphAlgorithms::AdjacencyMatrixPrepare(matrix_uint32_t &adjacency_matrix,
                                             size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (i == j) {
        adjacency_matrix[i][j] = 0;
      } else if (adjacency_matrix[i][j] == 0) {
        adjacency_matrix[i][j] = INF;
      }
    }
  }
}

GraphAlgorithms::matrix_uint32_t
GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
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
    size_t min = INF;
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

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  AntColonyOptimization colony(graph);
  return colony.SolveSalesmansProblem();
}
} // namespace s21
