#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_S21_GRAPH_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_S21_GRAPH_H_

#include <_types/_uint32_t.h>
#include <vector>

namespace s21 {

class Graph {
public:
  using string = std::string;
  using matrix_uint32_t = std::vector<std::vector<uint32_t>>;

  Graph();
  Graph(size_t size);

  size_t GetSize() const noexcept { return size_; }
  matrix_uint32_t GetMatrix() const noexcept { return adjacency_matrix_; }

  void LoadGraphFromFile(const string filename);
  void SaveGraphToFile(const string filename);
  void ExportGraphToDot(const string filename);

private:
  bool GraphIsDirected();
  bool GraphIsFull();
  bool GraphIsWeighted();

  size_t size_;
  matrix_uint32_t adjacency_matrix_;
  bool directed_;
  bool weighted_;
};
} // namespace s21

#endif // A2_SIMPLENAVIGATOR_v1_0_CPP_S21_GRAPH_H_
