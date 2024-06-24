#include "s21_graph_algorithms.h"
#include <cmath>

int s21::GraphAlgorithms::GetShortestPathBetweenVertices(s21::Graph &graph, int vertex1, int vertex2) {
  Graph::matrix_uint32_t adjacency_matrix = graph.GetMatrix(); // матрица связей
  size_t size = graph.GetSize();
  int minimum_distance[size];       // минимальное расстояние
  int visit[size];                  // посещенные вершины
  int temp, minindex, min;
  int begin_vertex = vertex1-1;       // стартовая точка

  if (CheckCorrectVertex(vertex1, vertex2, (int)size)) {
    return 0;
  } else if (vertex1 == vertex2) {
    return adjacency_matrix[vertex1-1][vertex2-1];
  } else {

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
  }
  return minimum_distance[vertex2-1];
}

bool s21::GraphAlgorithms::CheckCorrectVertex(int vertex1, int vertex2, int size) {
  return vertex1 < 0 && vertex2 < 0 && vertex1 > size && vertex2 > size;
}