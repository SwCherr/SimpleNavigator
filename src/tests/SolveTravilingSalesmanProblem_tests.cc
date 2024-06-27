#include <gtest/gtest.h>

#include <cstddef>

#include "../core/s21_ant_colony.h"
#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"

using namespace s21;

TEST(GraphAlgorithms, SolveTSM_01) {
  Graph graph;
  graph.LoadGraphFromFile("examples/graph_examples.md");
  GraphAlgorithms algorithms;
  auto resultTSM = algorithms.SolveTravelingSalesmanProblem(graph);

  double expected_distance = 253;

  EXPECT_TRUE(resultTSM.distance < expected_distance + 2 &&
              resultTSM.distance > expected_distance - 2);
}

TEST(GraphAlgorithms, SolveTSM_02) {
  Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_oriented2.txt");
  GraphAlgorithms algorithms;
  auto resultTSM = algorithms.SolveTravelingSalesmanProblem(graph);

  double expected_distance = 104;

  EXPECT_EQ(resultTSM.distance, expected_distance);
}
