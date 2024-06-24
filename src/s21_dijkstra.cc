#include "s21_dijkstra.h"

int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2) {
  size_t size = graph.Getsize()
  int adjacency_matrix[size][size]; // матрица связей
  int minimum_distance[size];       // минимальное расстояние
  int visit[size];                  // посещенные вершины
  int temp, minindex, min;
  int begin_vertex = vertex1;       // стартовая точка

  //Инициализация посещений вершин и расстояний
  for (int i = 0; i < size; i++) {
    minimum_distance[i] = INFINITY;
    visit[i] = 0;
  }
  minimum_distance[begin_vertex] = 0; // стартовая точка

  // Шаг алгоритма
  do {
    minindex = INFINITY;
    min = INFINITY;
    for (int i = 0; i < size; i++) { 
      // Если вершину ещё не обошли и вес меньше min
      if ((visit[i] == 0) && (minimum_distance[i] < min)) { 
        min = minimum_distance[i];
        minindex = i;
      }
    }
    
    // Добавляем найденный минимальный вес к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != INFINITY) {
      for (int i = 0; i < size; i++) {
        if (adjacency_matrix[minindex][i] > 0) {
          temp = min + adjacency_matrix[minindex][i];
          if (temp < minimum_distance[i]) {
            minimum_distance[i] = temp;
          }
        }
      }
      visit[minindex] = 1;
    }
  } while (minindex < INFINITY);


  // // Вывод кратчайших расстояний до вершин
  // printf("\nКратчайшие расстояния до вершин: \n");
  // for (int i = 0; i < size; i++)
  //   printf("%5d ", minimum_distance[i]);

  // // Восстановление пути
  // int ver[size]; // массив посещенных вершин
  // int end = 4; // индекс конечной вершины = 5 - 1
  // ver[0] = end + 1; // начальный элемент - конечная вершина
  // int k = 1; // индекс предыдущей вершины
  // int weight = minimum_distance[end]; // вес конечной вершины

  // while (end != begin_vertex) // пока не дошли до начальной вершины
  // {
  //   for (int i = 0; i < size; i++) // просматриваем все вершины
  //     if (adjacency_matrix[i][end] != 0)   // если связь есть
  //     {
  //       int temp = weight - adjacency_matrix[i][end]; // определяем вес пути из предыдущей вершины
  //       if (temp == minimum_distance[i]) // если вес совпал с рассчитанным
  //       {                 // значит из этой вершины и был переход
  //         weight = temp; // сохраняем новый вес
  //         end = i;       // сохраняем предыдущую вершину
  //         ver[k] = i + 1; // и записываем ее в массив
  //         k++;
  //       }
  //     }
  // }

  return minimum_distance[vertex2];
}