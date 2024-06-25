#include "s21_graph_algorithms.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

int s21::GraphAlgorithms::GetShortestPathBetweenVertices(s21::Graph &graph,
                                                         size_t from,
                                                         size_t to) {
  if (from > graph.GetSize() || to > graph.GetSize()) {
    throw std::out_of_range("Invalid values for vertexes");
  } else if (from == to) {
    return graph.GetMatrix()[from - 1][to - 1];
  }

  Graph::matrix_uint32_t adjacency_matrix = graph.GetMatrix(); // матрица связей
  size_t size = graph.GetSize();
  int minimum_distance[size]; // минимальное расстояние
  int visit[size];            // посещенные вершины
  int temp, minindex, min;
  int begin_vertex = from - 1; // стартовая точка

  //Инициализация посещений вершин и расстояний
  for (size_t i = 0; i < size; i++) {
    minimum_distance[i] = MAX_VALUE;
    visit[i] = 0;
  }
  minimum_distance[begin_vertex] = 0; // стартовая точка

  do {
    minindex = MAX_VALUE;
    min = MAX_VALUE;

    for (size_t i = 0; i < size; i++) {
      // Если вершину ещё не обошли и вес меньше INFINITY
      if ((visit[i] == 0) && (minimum_distance[i] < min)) {
        min = minimum_distance[i];
        minindex = i;
      }
    }

    // Добавляем найденный минимальный вес к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != MAX_VALUE) {
      for (size_t i = 0; i < size; i++) {
        if (adjacency_matrix[minindex][i] > 0) {
          temp = min + adjacency_matrix[minindex][i];
          if (temp < minimum_distance[i]) {
            minimum_distance[i] = temp;
          }
        }
      }
      visit[minindex] = 1;
    }
  } while (minindex < MAX_VALUE);

  return minimum_distance[to - 1];
}

s21::GraphAlgorithms::matrix_uint32_t s21::GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  matrix_uint32_t matrix = graph.GetMatrix();
  AdjacencyMatrixPrepare(matrix, graph.GetSize());
  for (size_t k = 0; k < graph.GetSize(); k++) {
    for (size_t i = 0; i < graph.GetSize(); i++) {
      for (size_t j = 0; j < graph.GetSize(); j++) {
        matrix[i][j] = std::min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
  return matrix;
}

void s21::GraphAlgorithms::AdjacencyMatrixPrepare(
    s21::GraphAlgorithms::matrix_uint32_t &adjacency_matrix, size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      if (i == j) {
        adjacency_matrix[i][j] = 0;
      } else if (adjacency_matrix[i][j] == 0) {
        adjacency_matrix[i][j] = MAX_VALUE;
      }
    }
  }
}

s21::GraphAlgorithms::matrix_uint32_t s21::GraphAlgorithms::GetLeastSpanningTree(Graph &graph) {
  size_t size = graph.GetSize();
  matrix_uint32_t matrix = graph.GetMatrix();
  matrix_uint32_t matrix_res(size, std::vector<uint32_t>(size));
  AdjacencyMatrixPrepare(matrix, size);

  size_t no_edge = 0;           
  int selected[size];
  memset(selected, false, sizeof (selected));
  selected[0] = true;  // choose 0th vertex and make it true
 
  size_t x, y;
  while (no_edge < size - 1) {
    size_t min = MAX_VALUE;
    x = 0;
    y = 0;

    for (size_t i = 0; i < size; i++) {
      if (selected[i]) {
        for (size_t j = 0; j < size; j++) {
          if (!selected[j] && matrix[i][j]) {
            if (min > matrix[i][j]) {
              min = matrix[i][j];
              x = i;
              y = j;
            }
          }
        }
      }
    }
    matrix_res[x][y] = matrix[x][y];
    selected[y] = true;
    no_edge++;
  }
 return matrix_res;
}

