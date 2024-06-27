#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"
#include <gtest/gtest.h>

TEST(GraphAlhorithms, min_spanning_tree) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/min_spanning_tree.txt");

  s21::Graph expected_graph;
  expected_graph.LoadGraphFromFile("examples/min_spanning_tree_result.txt");

  s21::GraphAlgorithms algorithms;

  auto result_matrix = algorithms.GetLeastSpanningTree(graph);
  auto expected_matrix = expected_graph.GetMatrix();

  for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
    for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
      std::cout << result_matrix[row][col] << ' ';
      // EXPECT_EQ(result_matrix[row][col], expected_matrix[row][col]);
    }
    std::cout << '\n';
  }

  std::cout << '\n';

  for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
    for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
      std::cout << expected_matrix[row][col] << ' ';
      // EXPECT_EQ(result_matrix[row][col], expected_matrix[row][col]);
    }
    std::cout << '\n';
  }
}
