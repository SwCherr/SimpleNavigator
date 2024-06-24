#include "s21_graph.h"

#include <_types/_uint32_t.h>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace s21 {
Graph::Graph() : size_(1), directed_(false), weighted_(false) {
  adjacency_matrix_ = matrix(size_, std::vector<uint32_t>(size_));
}

Graph::Graph(size_t size) : size_(size), directed_(false), weighted_(false) {
  if (size < 1) {
    throw std::out_of_range("Graph size shouldn't be less than 1");
  }

  adjacency_matrix_ = matrix(size_, std::vector<uint32_t>(size_));
}

void Graph::LoadGraphFromFile(string filename) {
  std::ifstream input(filename);
  if (!input) {
    throw std::invalid_argument("No such file.\n");
  }

  size_t size, tmp;
  input >> size;
  Graph result(size);

  for (size_t col = 0; col != size; ++col) {
    for (size_t row = 0; row != size; ++row) {
      if (!input.eof()) {
        input >> tmp;
        if (tmp > 1) {
          weighted_ = true;
        }
        adjacency_matrix_[row][col] = tmp;
      } else {
        throw std::length_error("Not enough data in the file");
      }
    }
  }

  if (GraphIsDirected()) {
    directed_ = true;
  }

  input.close();
}

} // namespace s21
