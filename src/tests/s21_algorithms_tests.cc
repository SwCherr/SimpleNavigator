#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"
#include <gtest/gtest.h>

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_FromFile_1_2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_2.txt");

  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 1, 2);
  int res_check = 7;
  EXPECT_EQ(res, res_check);
}

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_FromFile_1_3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_2.txt");

  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 1, 3);
  int res_check = 9;
  EXPECT_EQ(res, res_check);
}

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_FromFile_1_4) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_2.txt");

  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 1, 4);
  int res_check = 20;
  EXPECT_EQ(res, res_check);
}

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_FromFile_1_5) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_2.txt");

  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 1, 5);
  int res_check = 20;
  EXPECT_EQ(res, res_check);
}

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_FromFile_1_6) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_2.txt");

  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 1, 6);
  int res_check = 11;
  EXPECT_EQ(res, res_check);
}

TEST(GraphAlgorithms, GetShortestPathBetweenVertices_FromFile_WhithLoop) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix.txt");

  s21::GraphAlgorithms graph_alg;
  int res = graph_alg.GetShortestPathBetweenVertices(graph, 5, 5);
  int res_check = 1;
  EXPECT_EQ(res, res_check);
}

TEST(GraphAlgorithms,
     GetShortestPathBetweenOutOfRangeVertices_FromValidMatrix) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix.txt");

  s21::GraphAlgorithms graph_alg;
  EXPECT_ANY_THROW(graph_alg.GetShortestPathBetweenVertices(graph, 8, 5));
}
