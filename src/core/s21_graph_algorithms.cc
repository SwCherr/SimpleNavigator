#include "s21_graph_algorithms.h"
#include <cmath>


// ПЕРЕДЕЛАТЬ С УЧЕТОМ НУМЕРАЦИИС 1 !!!!!
int s21::GraphAlgorithms::GetShortestPathBetweenVertices(s21::Graph &graph, int vertex1, int vertex2) {
  size_t size = graph.GetSize();
  int adjacency_matrix[size][size]; // матрица связей
  unsigned int minimum_distance[size];       // минимальное расстояние
  unsigned int visit[size];                  // посещенные вершины
  // int temp, 
  unsigned int minindex, min;
  int begin_vertex = vertex1;       // стартовая точка

  //Инициализация посещений вершин и расстояний
  for (size_t i = 0; i < size; i++) {
    minimum_distance[i] = MAX_VALUE;
    visit[i] = 0;
  }
  minimum_distance[begin_vertex] = 0; // стартовая точка



  int i = 1;
  // Шаг алгоритма
  do {
    minindex = MAX_VALUE;
    min = MAX_VALUE;
    printf("index = %d\n", i);
    i++;

    for (size_t i = 0; i < size; i++) { 
      // Если вершину ещё не обошли и вес меньше min
      printf("MAF i = %zu\n", i);
      printf("minimum_distance[i] = %u\n", minimum_distance[i]);

      if ((visit[i] == 0) && (minimum_distance[i] < min)) {
        min = minimum_distance[i];
        minindex = i;
        printf("minindex = %d\n", minindex);
      }
    }
    
    // Добавляем найденный минимальный вес к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != MAX_VALUE) {
      for (size_t i = 0; i < size; i++) {
        printf("MAF\n");
        if (adjacency_matrix[minindex][i] > 0) {
          // temp = min + adjacency_matrix[minindex][i];
          // if (temp < minimum_distance[i]) {
          //   minimum_distance[i] = temp;
          // }
        }
      }
      visit[minindex] = 1;
    }


  } while (minindex < MAX_VALUE);

  // return minimum_distance[vertex2]; // переделать на каунт, пока суммирует веса
  return vertex2; // переделать на каунт, пока суммирует веса
}