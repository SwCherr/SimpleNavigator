#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_CONTROLLER_S21_CONSOLE_CONTROLLER_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_CONTROLLER_S21_CONSOLE_CONTROLLER_H_

#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"
#include <_types/_uint32_t.h>

namespace s21 {
class ConsoleController {
public:
  ConsoleController(GraphAlgorithms *m) : model_(m), graph_(){};

  void PrintCurrentGraph() { graph_.PrintMatrixGraph(); }
  void LoadGraphFromFile(const std::string &filename) {
    graph_.LoadGraphFromFile(filename);
  }
  std::vector<uint32_t> BreadthFirstSearch(uint32_t startVertex) {
    return model_->BreadthFitstSearch(graph_, startVertex);
  }
  std::vector<uint32_t> DepthFirstSearch(uint32_t startVertex) {
    return model_->DepthFirstSearch(graph_, startVertex);
  }
  size_t GetShortestPathBetweenVerteces(uint32_t firstVertex,
                                        uint32_t lastVertex) {
    return model_->GetShortestPathBetweenVertices(graph_, firstVertex,
                                                  lastVertex);
  }
  void PrintShortestPathBetweenAllVerteces() {
    auto matrix = model_->GetShortestPathsBetweenAllVertices(graph_);
    PrintMatrixUint32_t(matrix);
  };

private:
  void PrintMatrixUint32_t(Graph::matrix_uint32_t matrix);

  GraphAlgorithms *model_;
  Graph graph_;
};
} // namespace s21

#endif // A2_SIMPLENAVIGATOR_v1_0_CPP_CONTROLLER_S21_CONSOLE_CONTROLLER_H_
