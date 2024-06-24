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
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix.txt");
  EXPECT_EQ(graph.GetSize(), 5);
}
