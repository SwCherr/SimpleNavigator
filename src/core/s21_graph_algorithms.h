#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_ALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_ALGORITHMS_H_

#include "s21_graph.h"
#include <_types/_uint32_t.h>
#include <climits>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

namespace s21 {
using std::vector;

class GraphAlgorithms {
public:
  using matrix_uint32_t = vector<std::vector<uint32_t>>;

  const uint32_t kMax = std::numeric_limits<uint32_t>::max();

  vector<uint32_t> DepthFirstSearch(const Graph &graph, uint32_t start_vertex);
  vector<uint32_t> BreadthFitstSearch(const Graph &graph,
                                      uint32_t start_vertex);

  size_t GetShortestPathBetweenVertices(Graph &graph, uint32_t from,
                                        uint32_t to);
  matrix_uint32_t GetShortestPathsBetweenAllVertices(Graph &graph);
  matrix_uint32_t GetLeastSpanningTree(Graph &graph);

private:
  std::vector<std::vector<bool>>
  ClosestPath(const matrix_uint32_t &adjacency_matrix);
  void AdjacencyMatrixPrepare(matrix_uint32_t &adjacency_matrix, size_t size);
};

} // namespace s21

#endif // A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_ALGORITHMS_H_
