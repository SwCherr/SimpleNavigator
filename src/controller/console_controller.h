#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_CONTROLLER_S21_CONSOLE_CONTROLLER_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_CONTROLLER_S21_CONSOLE_CONTROLLER_H_

#include <_types/_uint32_t.h>

#include <filesystem>
#include <iostream>

#include "../core/s21_graph.h"
#include "../core/s21_graph_algorithms.h"

namespace s21 {
class ConsoleController {
 public:
  ConsoleController(GraphAlgorithms *m) : model_(m), graph_(){};

  void PrintCurrentGraph() {
    if (graph_.Empty()) {
      std::cout << "Graph is empty.\n";
    } else {
      graph_.PrintMatrixGraph();
    }
  }

  void LoadGraphFromFile(const std::string &filename) {
    std::cout << '\n';
    if (std::filesystem::exists(filename)) {
      graph_.LoadGraphFromFile(filename);
    } else {
      std::cout << "File with name \"" << filename << "\" not exists";
    }
    std::cout << '\n';
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

  void PrintShortestPathsBetweenAllVerteces() {
    auto matrix = model_->GetShortestPathsBetweenAllVertices(graph_);
    PrintMatrixUint32_t(matrix);
  };

  void PrintLeastSpanningTree() {
    auto matrix = model_->GetLeastSpanningTree(graph_);
    PrintMatrixUint32_t(matrix);
  }

  void PrintSolveTravelingSelesmanProblem() {
    TsmResult result = model_->SolveTravelingSalesmanProblem(graph_);
    std::cout << "TSM path: ";
    for (size_t i = 0; i < result.vertexes.size(); ++i) {
      std::cout << result.vertexes[i] << ' ';
    }
    std::cout << "\nTSM distance: " << result.distance << '\n';
  }

 private:
  void PrintMatrixUint32_t(Graph::matrix_uint32_t matrix);

  GraphAlgorithms *model_;
  Graph graph_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_v1_0_CPP_CONTROLLER_S21_CONSOLE_CONTROLLER_H_
