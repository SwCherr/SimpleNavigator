#include "s21_graph_algorithms.h"
#include <cmath>


// ДОБАВИТЬ ПРОЕВЕРКИ НА ГРАНИЧНЫЕ ЗНАЧЕНИЯ ПОЛУЧАЕМЫХ КООРДИНАТ ТОЧЕК !!!!
// ДОБАВИТЬ ПРОВЕРКУ НА ПЕТЛИ
int s21::GraphAlgorithms::GetShortestPathBetweenVertices(s21::Graph &graph, int vertex1, int vertex2) {
  Graph::matrix_uint32_t adjacency_matrix = graph.GetMatrix(); // матрица связей
  size_t size = graph.GetSize();

  int minimum_distance[size];       // минимальное расстояние
  int visit[size];                  // посещенные вершины
  int temp, minindex, min;
  int begin_vertex = vertex1-1;       // стартовая точка

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
  return minimum_distance[vertex2-1];
}