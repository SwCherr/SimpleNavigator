#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_VIEW_S21_CONSOLE_VIEW_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_VIEW_S21_CONSOLE_VIEW_H_

#include "../controller/console_controller.h"
namespace s21 {

enum Choice {
  kExit = 0,
  kLoadGraphFromFile = 1,
  kBFS = 2,
  kDFS = 3,
  kGetShortPathBetweenVerteces = 4,
  kGetShortPathsBetweenAllVerteces = 5,
  kGetLeastSpanningTree = 6,
  kSolveTravelingSalesmanProblem = 7,
};

class ConsoleView {
 public:
  ConsoleView(ConsoleController *c) : controller_(c){};

  size_t inputVertex();
  void DisplayMenu();
  short performChoice();
  std::string filePathInput();
  void startEventLoop();

 private:
  void PrintVectorResult(vector<uint32_t> result);
  ConsoleController *controller_;
};
}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_CONSOLE_INTERFACE_H_
