#include <gtest/gtest.h>

#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"

TEST(GraphAlhorithms, min_spanning_tree_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/min_spanning_tree_1.txt");
  size_t size = graph.GetSize();

  s21::Graph expected_graph;
  expected_graph.LoadGraphFromFile("examples/min_spanning_tree_1_res.txt");

  s21::GraphAlgorithms algorithms;
  auto result_matrix = algorithms.GetLeastSpanningTree(graph);
  auto expected_matrix = expected_graph.GetMatrix();

  for (size_t row = 0; row < size; ++row) {
    for (size_t col = 0; col < size; ++col) {
      EXPECT_EQ(result_matrix[row][col], expected_matrix[row][col]);
    }
  }

  // std::cout << '\n';
  // for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
  //   for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
  //     std::cout << result_matrix[row][col] << ' ';
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << '\n';
  // for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
  //   for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
  //     std::cout << expected_matrix[row][col] << ' ';
  //   }
  //   std::cout << '\n';
  // }
}

TEST(GraphAlhorithms, min_spanning_tree_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/min_spanning_tree_2.txt");
  size_t size = graph.GetSize();

  s21::Graph expected_graph;
  expected_graph.LoadGraphFromFile("examples/min_spanning_tree_2_res.txt");

  s21::GraphAlgorithms algorithms;
  auto result_matrix = algorithms.GetLeastSpanningTree(graph);
  auto expected_matrix = expected_graph.GetMatrix();

  for (size_t row = 0; row < size; ++row) {
    for (size_t col = 0; col < size; ++col) {
      EXPECT_EQ(result_matrix[row][col], expected_matrix[row][col]);
    }
  }

  // std::cout << '\n';
  // for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
  //   for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
  //     std::cout << result_matrix[row][col] << ' ';
  //   }
  //   std::cout << '\n';
  // }
  // std::cout << '\n';
  // for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
  //   for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
  //     std::cout << expected_matrix[row][col] << ' ';
  //   }
  //   std::cout << '\n';
  // }
}

// TEST(GraphAlhorithms, GetLeastSpanningTreeDirected) {
//   s21::Graph graph;
//   graph.LoadGraphFromFile("examples/least_spanning_tree_directed.txt");
//
//   s21::Graph expected_graph;
//   expected_graph.LoadGraphFromFile(
//       "examples/least_spanning_tree_directed_result.txt");
//
//   s21::GraphAlgorithms algorithms;
//
//   auto result_matrix = algorithms.GetLeastSpanningTree(graph);
//   auto expected_matrix = expected_graph.GetMatrix();
//
//   for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
//     for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
//       std::cout << result_matrix[row][col] << ' ';
//       // EXPECT_EQ(result_matrix[row][col], expected_matrix[row][col]);
//     }
//     std::cout << '\n';
//   }
//
//   std::cout << '\n';
//
//   for (size_t row = 0; row < expected_graph.GetSize(); ++row) {
//     for (size_t col = 0; col < expected_graph.GetSize(); ++col) {
//       std::cout << expected_matrix[row][col] << ' ';
//       // EXPECT_EQ(result_matrix[row][col], expected_matrix[row][col]);
//     }
//     std::cout << '\n';
//   }
// }
