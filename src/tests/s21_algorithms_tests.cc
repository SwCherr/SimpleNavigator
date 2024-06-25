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

TEST(GraphAlgorithms, GetShortestPathsBetweenAllVertices_FromFile_1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("examples/valid_matrix_2.txt");
  size_t size = graph.GetSize();

  s21::GraphAlgorithms graph_alg;
  s21::GraphAlgorithms::matrix_uint32_t res_matrix =
      graph_alg.GetShortestPathsBetweenAllVertices(graph);
  s21::GraphAlgorithms::matrix_uint32_t check_matrix(
      size, std::vector<uint32_t>(size));

  check_matrix[0][0] = 0;
  check_matrix[0][1] = 7;
  check_matrix[0][2] = 9;
  check_matrix[0][3] = 20;
  check_matrix[0][4] = 20;
  check_matrix[0][5] = 11;

  check_matrix[1][0] = 7;
  check_matrix[1][1] = 0;
  check_matrix[1][2] = 10;
  check_matrix[1][3] = 15;
  check_matrix[1][4] = 21;
  check_matrix[1][5] = 12;

  check_matrix[2][0] = 9;
  check_matrix[2][1] = 10;
  check_matrix[2][2] = 0;
  check_matrix[2][3] = 11;
  check_matrix[2][4] = 11;
  check_matrix[2][5] = 2;

  check_matrix[3][0] = 20;
  check_matrix[3][1] = 15;
  check_matrix[3][2] = 11;
  check_matrix[3][3] = 0;
  check_matrix[3][4] = 6;
  check_matrix[3][5] = 13;

  check_matrix[4][0] = 20;
  check_matrix[4][1] = 21;
  check_matrix[4][2] = 11;
  check_matrix[4][3] = 6;
  check_matrix[4][4] = 0;
  check_matrix[4][5] = 9;

  check_matrix[5][0] = 11;
  check_matrix[5][1] = 12;
  check_matrix[5][2] = 2;
  check_matrix[5][3] = 13;
  check_matrix[5][4] = 9;
  check_matrix[5][5] = 0;

  // for (size_t i = 0; i < size; i++) {
  //   for (size_t j = 0; j < size; j++) {
  //     printf("%d ", res_matrix[i][j]);
  //   }
  //   printf("\n");
  // }

  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      EXPECT_EQ(check_matrix[i][j], res_matrix[i][j]);
    }
  }
}
