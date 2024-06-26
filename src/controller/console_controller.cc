#include "console_controller.h"

#include <iostream>

namespace s21 {
void ConsoleController::PrintMatrixUint32_t(Graph::matrix_uint32_t matrix) {
  for (size_t row = 0; row < matrix.front().size(); ++row) {
    for (size_t col = 0; col < matrix.size(); ++col) {
      std::cout << matrix[row][col] << ' ';
    }
    std::cout << '\n';
  }
}
} // namespace s21
