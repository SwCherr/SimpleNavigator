#include "s21_graph.h"
#include <climits>
#include <stdio.h>
#include <stdlib.h>

#define MAX_VALUE INT_MAX

namespace s21 {

class GraphAlgorithms {
public:
  int GetShortestPathBetweenVertices(s21::Graph &graph, size_t from, size_t to);
};

} // namespace s21
