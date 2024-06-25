#include "../core/s21_graph.h"
#include <gtest/gtest.h>

TEST(Graph, Construct) {
  s21::Graph graph;
  EXPECT_EQ(graph.GetSize(), 1);
}

TEST(Graph, ConstrucWithParams) {
  s21::Graph graph(2);
  s21::Graph::matrix_uint32_t matrix = graph.GetMatrix();

  EXPECT_EQ(graph.GetSize(), 2);
  EXPECT_EQ(matrix[0][0], 0);
  EXPECT_EQ(matrix[0][1], 0);
  EXPECT_EQ(matrix[1][0], 0);
  EXPECT_EQ(matrix[1][1], 0);
}

TEST(Graph, LoadFromFile) {
  // expected
  s21::Graph::matrix_uint32_t expected_matrix(5, std::vector<uint32_t>(5));
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
  EXPECT_EQ(graph.GetSize(), 5);
  for (size_t row = 0; row < graph.GetSize(); ++row) {
    for (size_t col = 0; col < graph.GetSize(); ++col) {
      EXPECT_EQ(received_matrix[row][col], expected_matrix[row][col]);
    }
  }
}

TEST(Graph, LoadFromNotExistFile) {
  s21::Graph graph;
  EXPECT_ANY_THROW(graph.LoadGraphFromFile("exam/exam"));
}

TEST(Graph, LoadFromIncorrectFile) {
  s21::Graph graph;
  EXPECT_ANY_THROW(graph.LoadGraphFromFile("examples/invalid_matrix.txt"));
}

TEST(Graph, ExportGraphToDot) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix.txt");
  graph.ExportGraphToDot("examples/dot_matr.txt");
}
