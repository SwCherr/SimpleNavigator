#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_H_

#include <_types/_uint32_t.h>

#include <string>
#include <vector>

namespace s21 {

class Graph {
 public:
  using matrix_uint32_t = std::vector<std::vector<uint32_t>>;

  Graph();
  Graph(size_t size);
  Graph(const matrix_uint32_t &matrix);

  size_t GetSize() const noexcept { return size_; }
  matrix_uint32_t GetMatrix() const noexcept { return adjacency_matrix_; }

  void LoadGraphFromFile(const std::string &filename);
  void ExportGraphToDot(const std::string &filename);

  bool GraphIsDirected();
  bool GraphIsWeighted();
  bool Empty() { return size_ == 1 && adjacency_matrix_[0][0] == 0; }

 private:
  size_t size_;
  matrix_uint32_t adjacency_matrix_;
  bool directed_;
  bool weighted_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_GRAPH_H_
