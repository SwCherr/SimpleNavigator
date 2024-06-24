#include "s21_graph.h"

#include <_types/_uint32_t.h>
#include <fstream>
#include <stdexcept>
#include <vector>

namespace s21 {
Graph::Graph() : size_(1), directed_(false), weighted_(false) {
  adjacency_matrix_ = matrix_uint32_t(size_, std::vector<uint32_t>(size_));
}

Graph::Graph(size_t size) : size_(size), directed_(false), weighted_(false) {
  if (size < 1) {
    throw std::out_of_range("Graph size shouldn't be less than 1");
  }

  adjacency_matrix_ = matrix_uint32_t(size_, std::vector<uint32_t>(size_));
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

  directed_ = GraphIsDirected();

  input.close();
}

void Graph::ExportGraphToDot(string filename) {
  std::ofstream output;

  if (output.is_open() == false) {
    throw std::logic_error("Couldn't open file.");
  }

  if (directed_) {
    output << "directed graph {\n";
  } else {
    output << "graph {\n";
  }

  for (size_t row = 0; row < size_; ++row) {
    for (size_t col = 0; col < size_; ++col) {
      output << "\t" << row + 1;
      string direction = directed_ ? " -> " : " -- ";
      output << direction;
      output << col + 1 << " [weight=" << adjacency_matrix_[row][col] << "]\n;";
    }
  }
  output << "}\n";

  output.close();
}

void Graph::SaveGraphToFile(string filename) {
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
