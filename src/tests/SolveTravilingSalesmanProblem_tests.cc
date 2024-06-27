#include "../core/s21_ant_colony.h"
#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"
#include <gtest/gtest.h>

using namespace s21;

TEST(GraphAlgorithms, SolveTSM_01) {
  Graph graph;
  graph.LoadGraphFromFile("examples/graph_examples.md");
  GraphAlgorithms algorithms;
  auto resultTSM = algorithms.SolveTravelingSalesmanProblem(graph);

  double expected_distance = 253;
  vector<size_t> expected_traveling_vertices = {1, 8, 5, 4,  10, 6,
                                                3, 7, 2, 11, 9,  1};

  for (size_t i = 0; i < resultTSM.vertexes.size(); ++i) {
    EXPECT_EQ(resultTSM.vertexes[i], expected_traveling_vertices[i]);
  }
  EXPECT_EQ(resultTSM.distance, expected_distance);
}
