#include "s21_console_view.h"

#include <iostream>
#include <vector>

namespace s21 {
using std::cin;
using std::cout;
using std::vector;

void ConsoleView::DisplayMenu() {
  cout << "\n MENU \nCurrent graph:\n";
  controller_->PrintCurrentGraph();
  cout << '\n';

  cout << "1. Load new graph from file\n";
  cout << "2. DeepFirstSearch\n";
  cout << "3. BreadthFirstSearch\n";
  cout << "4. GetShortestPathBetweenVerteces\n";
  cout << "5. GetShortestPathBetweenAllVerteces\n";
  cout << "6. \n";
  cout << "0. Quit\n\n";
}

short ConsoleView::performChoice() {
  short choice;
  cout << "Input a menu item digit: ";
  cin >> choice;
  return choice;
}

size_t ConsoleView::inputVertex() {
  size_t vertex;
  cout << "Input a first number of vertex: ";
  cin >> vertex;
  return vertex;
}

void ConsoleView::startEventLoop() {
  while (true) {
    std::string fileName;
    size_t firstVertex;
    size_t lastVertex;
    DisplayMenu();

    switch ((Choice)performChoice()) {
    case kLoadGraphFromFile:
      cout << "Enter path to file\n";
      cin >> fileName;
      controller_->LoadGraphFromFile(fileName);
      break;
    case kBFS:
      firstVertex = inputVertex();
      PrintVectorResult(controller_->BreadthFirstSearch(firstVertex));
      break;
    case kDFS:
      firstVertex = inputVertex();
      PrintVectorResult(controller_->DepthFirstSearch(firstVertex));
      break;
    case kGetShortPathBetweenVerteces:
      firstVertex = inputVertex();
      lastVertex = inputVertex();
      cout << controller_->GetShortestPathBetweenVerteces(firstVertex,
                                                          lastVertex);
      break;
    case kGetShortPathBetweenAllVerteces:
      controller_->PrintShortestPathBetweenAllVerteces();
      break;
    case kGetLeastSpanningTree:
      break;
    case kSolveTravelingSalesmanProblem:
      break;
    case kExit:
      exit(1);

    default:
      cout << "Wrong menu item number!";
      continue;
    }
  }
}

void ConsoleView::PrintVectorResult(vector<uint32_t> result) {
  cout << "Result is: ";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i] << ' ';
  }
  cout << '\n';
}

} // namespace s21
