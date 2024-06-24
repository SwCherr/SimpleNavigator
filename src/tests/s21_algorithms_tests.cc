#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"
#include <gtest/gtest.h>

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_1) {
  s21::Graph graph(5);
  graph.PrintMatrixGraph();


  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 1, 4);
  EXPECT_EQ(res, 0);
}
