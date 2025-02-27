#include <gtest/gtest.h>

#include "../core/s21_graph.h"

TEST(Graph, Construct) {
  s21::Graph graph;
  size_t expected_size = 1;
  EXPECT_EQ(graph.GetSize(), expected_size);
}

TEST(Graph, ConstrucWithParams) {
  s21::Graph graph(2);
  s21::Graph::matrix_uint32_t matrix = graph.GetMatrix();

  size_t expected_size = 2;

  EXPECT_EQ(graph.GetSize(), expected_size);
  EXPECT_EQ(matrix[0][0], (size_t)0);
  EXPECT_EQ(matrix[0][1], (size_t)0);
  EXPECT_EQ(matrix[1][0], (size_t)0);
  EXPECT_EQ(matrix[1][1], (size_t)0);
}

TEST(Graph, ConstructWithMatrix) {
  s21::Graph::matrix_uint32_t expected_matrix = {
      {1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
  s21::Graph graph(expected_matrix);
  s21::Graph::matrix_uint32_t graph_matrix = graph.GetMatrix();
  for (size_t row = 0; row < 3; ++row) {
    for (size_t col = 0; col < 3; ++col) {
      EXPECT_EQ(expected_matrix[row][col], graph_matrix[row][col]);
    }
  }
}

TEST(Graph, GraphIsWeighted) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/deep_graph.txt");
  EXPECT_FALSE(graph.GraphIsWeighted());
  graph.LoadGraphFromFile("examples/valid_matrix.txt");
  EXPECT_TRUE(graph.GraphIsWeighted());
}

TEST(Graph, LoadFromFile) {
  // expected
  s21::Graph::matrix_uint32_t expected_matrix(5, std::vector<uint32_t>(5));
  size_t expected_size = 5;
  expected_matrix[0][0] = 0;
  expected_matrix[0][1] = 8;
  expected_matrix[0][2] = 0;
  expected_matrix[0][3] = 1;
  expected_matrix[0][4] = 1;

  expected_matrix[1][0] = 0;
  expected_matrix[1][1] = 0;
  expected_matrix[1][2] = 1;
  expected_matrix[1][3] = 0;
  expected_matrix[1][4] = 1;

  expected_matrix[2][0] = 0;
  expected_matrix[2][1] = 1;
  expected_matrix[2][2] = 0;
  expected_matrix[2][3] = 1;
  expected_matrix[2][4] = 1;

  expected_matrix[3][0] = 6;
  expected_matrix[3][1] = 0;
  expected_matrix[3][2] = 1;
  expected_matrix[3][3] = 0;
  expected_matrix[3][4] = 1;

  expected_matrix[4][0] = 1;
  expected_matrix[4][1] = 1;
  expected_matrix[4][2] = 1;
  expected_matrix[4][3] = 1;
  expected_matrix[4][4] = 1;

  // received
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix.txt");
  s21::Graph::matrix_uint32_t received_matrix = graph.GetMatrix();

  // test
  EXPECT_EQ(graph.GetSize(), expected_size);
  for (size_t row = 0; row < graph.GetSize(); ++row) {
    for (size_t col = 0; col < graph.GetSize(); ++col) {
      EXPECT_EQ(received_matrix[row][col], expected_matrix[row][col]);
    }
  }
}

TEST(Graph, ExportGraphToDot) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix.txt");
  graph.ExportGraphToDot("examples/dot_matr.txt");
}
