#include "s21_graph.h"

#include <_types/_uint32_t.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sys/_types/_int64_t.h>
#include <vector>

namespace s21 {

void Graph::PrintMatrixGraph() {
  for (size_t i = 0; i < size_; i++) {
    for (size_t j = 0; j < size_; j++) {
      printf("%d ", adjacency_matrix_[i][j]);
    }
    printf("\n");
  }
}

Graph::Graph() : size_(1), directed_(false), weighted_(false) {
  adjacency_matrix_ = matrix_uint32_t(size_, std::vector<uint32_t>(size_));
}

Graph::Graph(size_t size) : size_(size), directed_(false), weighted_(false) {
  if (size < 1) {
    throw std::out_of_range("Graph size shouldn't be less than 1");
  }

  adjacency_matrix_ = matrix_uint32_t(size_, std::vector<uint32_t>(size_));
}

Graph::Graph(const matrix_uint32_t &matrix) {
  if (matrix.front().size() != matrix.size()) {
    throw std::runtime_error("Failed to construct graph from matrix.");
  }

  size_ = adjacency_matrix_.size();
  adjacency_matrix_ = matrix_uint32_t(size_, std::vector<uint32_t>(size_));
  if (size_ != 0) {
    for (size_t row = 0; row < size_; ++row) {
      for (size_t col = 0; col < size_; ++col) {
        auto value = matrix[row][col];
        if (value > 1) {
          weighted_ = true;
        }
        adjacency_matrix_[row][col] = value;
      }
    }
  }
}

void Graph::LoadGraphFromFile(const std::string &filename) {
  std::ifstream input(filename);
  if (!input) {
    throw std::runtime_error("Failed to open file.");
  }

  input >> size_;
  if (input.fail() || size_ < 1) {
    throw std::runtime_error("Failed to read size of graph.");
  }

  adjacency_matrix_.clear();
  adjacency_matrix_.resize(size_, std::vector<uint32_t>(size_));

  int64_t tmp;
  for (size_t row = 0; row < size_; ++row) {
    for (size_t col = 0; col < size_; ++col) {
      if (input >> tmp) {
        if (tmp < 0) {
          throw std::out_of_range(filename + "constraint negative value!");
        } else if (tmp > 1) {
          weighted_ = true;
        }
        adjacency_matrix_[row][col] = tmp;
      } else {
        throw std::runtime_error("Failed to read data from file.");
      }
    }
  }

  directed_ = GraphIsDirected();
  input.close();
}

void Graph::ExportGraphToDot(const std::string &filename) {
  std::ofstream output;
  output.open(filename);

  if (output.is_open() == false) {
    throw std::logic_error("Couldn't open file.");
  }

  if (directed_) {
    output << "digraph {\n";
  } else {
    output << "graph {\n";
  }

  for (size_t row = 0; row < size_; ++row) {
    for (size_t col = 0; col < size_; ++col) {
      output << "\t" << row + 1;
      std::string direction =
          adjacency_matrix_[row][col] == adjacency_matrix_[col][row] ? " -- "
                                                                     : " -> ";
      output << direction;
      output << col + 1 << " [weight=" << adjacency_matrix_[row][col] << "];\n";
    }
  }
  output << "}\n";

  output.close();
}

void Graph::SaveGraphToFile(const std::string &filename) {
  std::ofstream output;
  output.open(filename);

  if (output.is_open() == false) {
    throw std::logic_error("Couldn't open file.");
  }

  output << size_ << '\n';
  for (size_t row = 0; row < size_; ++row) {
    for (size_t col = 0; col < size_ - 1; ++col) {
      output << adjacency_matrix_[row][col] << ' ';
    }
    output << adjacency_matrix_[row][size_ - 1] << '\n';
  }

  output.close();
}

bool Graph::GraphIsDirected() {
  size_t edges_count = 0;
  size_t reverse_edjes_count = 0;

  for (size_t row = 0; row != size_; ++row) {
    for (size_t col = 0; col != size_; ++col) {
      if (adjacency_matrix_[row][col]) {
        ++edges_count;
        if (adjacency_matrix_[row][col] == adjacency_matrix_[col][row]) {
          ++reverse_edjes_count;
        }
      }
    }
  }
  return edges_count != reverse_edjes_count;
}

bool Graph::GraphIsFull() {
  bool is_full = true;
  for (size_t row = 0; row != size_ && is_full; ++row) {
    for (size_t col = 0; col != size_ && is_full; ++col) {
      if (adjacency_matrix_[row][col] == 0 && row != col) {
        is_full = false;
      }
    }
  }

  return is_full;
}

bool Graph::GraphIsWeighted() {
  bool is_weighted = false;
  for (size_t row = 0; row != size_ && !is_weighted; ++row) {
    for (size_t col = 0; col != size_ && !is_weighted; ++col) {
      if (adjacency_matrix_[row][col] > 1) {
        is_weighted = true;
      }
    }
  }

  return is_weighted;
}

} // namespace s21
