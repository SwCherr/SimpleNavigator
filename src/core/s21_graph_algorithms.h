#include <stdio.h>
#include <stdlib.h>
#include "s21_graph.h"
#define MAX_VALUE INT_MAX

namespace s21 {
  
class GraphAlgorithms {
public:
  using matrix_uint32_t = std::vector<std::vector<uint32_t>>;

  int GetShortestPathBetweenVertices(s21::Graph &graph, int vertex1, int vertex2);
  matrix_uint32_t GetShortestPathsBetweenAllVertices(Graph &graph);
  void AdjacencyMatrixPrepare(matrix_uint32_t &adjacency_matrix, size_t size);
  bool CheckCorrectVertex(int vertex1, int vertex2, int size);
};

}
