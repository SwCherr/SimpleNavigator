#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_S21_GRAPH_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_S21_GRAPH_H_

#include <_types/_uint32_t.h>
#include <vector>

namespace s21 {

class Graph {
public:
  using string = std::string;
  using matrix = std::vector<std::vector<uint32_t>>;

  Graph();
  Graph(size_t size);

  uint32_t GetSize() const noexcept { return size_; }
  matrix GetMatrix() const noexcept { return adjacency_matrix_; }

  void LoadGraphFromFile(string filename);
  void ExportGraphToDot(string filename);

  bool GraphIsDirected();
  bool GraphIsFull();
  bool GraphIsWeighted();
  void SaveGraphToFile(string filename);

private:
  size_t size_;
  matrix adjacency_matrix_;
  bool directed_;
  bool weighted_;
};
} // namespace s21

#endif // A2_SIMPLENAVIGATOR_v1_0_CPP_S21_GRAPH_H_
