#include "../core/s21_graph_algorithms.h"
#include <_types/_uint32_t.h>
#include <gtest/gtest.h>

// vector<uint32_t> DepthFirstSearch(const Graph &graph, uint32_t start_vertex);
// vector<uint32_t> BreadthFitstSeatch(const Graph &graph,
//                                     uint32_t start_vertex);

TEST(GraphAlgorithmsSearch, DepthFirstSearch_01) {
  s21::Graph graph;
  s21::GraphAlgorithms graphAlgorithms;
  graph.LoadGraphFromFile("examples/graph_algorithm.txt");
  std::vector<uint32_t> expected_vector = {4, 1, 2, 3, 5};
  auto result_vector = graphAlgorithms.DepthFirstSearch(graph, 4);
  for (size_t i = 0; i < expected_vector.size(); ++i) {
    EXPECT_EQ(expected_vector[i], result_vector[i]);
  }
}

TEST(GraphAlgorithmsSearch, BreadthFitstSeatch_01) {
  s21::Graph graph;
  s21::GraphAlgorithms graphAlgorithms;
  graph.LoadGraphFromFile("examples/graph_algorithm.txt");
  std::vector<uint32_t> expected_vector = {4, 1, 3, 5, 2};
  auto result_vector = graphAlgorithms.BreadthFitstSearch(graph, 4);
  for (size_t i = 0; i < expected_vector.size(); ++i) {
    EXPECT_EQ(expected_vector[i], result_vector[i]);
  }
}
