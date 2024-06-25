#include "s21_graph.h"
#include <climits>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE INT_MAX

namespace s21 {

class GraphAlgorithms {
public:
  using matrix_uint32_t = std::vector<std::vector<uint32_t>>;

  int GetShortestPathBetweenVertices(s21::Graph &graph, size_t from, size_t to);
  matrix_uint32_t GetShortestPathsBetweenAllVertices(Graph &graph);
  void AdjacencyMatrixPrepare(matrix_uint32_t &adjacency_matrix, size_t size);
  matrix_uint32_t GetLeastSpanningTree(Graph &graph);
};

} // namespace s21
