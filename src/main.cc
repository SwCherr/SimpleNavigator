#include "controller/console_controller.h"
#include "core/s21_graph_algorithms.h"
#include "view/s21_console_view.h"

int main() {
  s21::GraphAlgorithms graph_model;
  s21::ConsoleController graph_controller(&graph_model);
  s21::ConsoleView graph_view(&graph_controller);
  graph_view.startEventLoop();
  return 0;
}
