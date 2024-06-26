#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_ALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_ALGORITHMS_H_

#include "s21_graph.h"
#include "s21_ant_colony.h"
#include <_types/_uint32_t.h>
#include <climits>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// #define MAX_VALUE INT_MAX
#define INF 1000000000

namespace s21 {
using std::vector;

class GraphAlgorithms {
public:
  using matrix_uint32_t = vector<std::vector<uint32_t>>;
  using TsmResult = struct TsmResult;

  vector<uint32_t> DepthFirstSearch(const Graph &graph, uint32_t start_vertex);
  vector<uint32_t> BreadthFitstSearch(const Graph &graph,
                                      uint32_t start_vertex);

  int GetShortestPathBetweenVertices(Graph &graph, size_t from, size_t to);
  matrix_uint32_t GetShortestPathsBetweenAllVertices(Graph &graph);
  matrix_uint32_t GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);

private:
  void AdjacencyMatrixPrepare(matrix_uint32_t &adjacency_matrix, size_t size);
};

} // namespace s21

#endif // A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_ALGORITHMS_H_
