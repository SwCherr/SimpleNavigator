#ifndef A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_ANT_COLONY_H_
#define A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_ANT_COLONY_H_

#include "s21_graph.h"
#define INF 1000000000

namespace s21 {
struct TsmResult {
  std::vector<std::size_t> vertexes;
  double distance = 0;
};

struct Ant {
  using Matrix = std::vector<std::vector<double>>;
  explicit Ant(std::size_t start_vertex = 0) : start_location(start_vertex), current_location(start_vertex) {}; //// explicit

  TsmResult path;
  std::vector<std::size_t> visited;
  std::size_t start_location = 0;
  std::size_t current_location = 0;
  bool can_continue = true;

  void MakeChoice(const Graph &g, const Matrix &p, double a, double b);
  double GetRandomChoice();
  std::vector<std::size_t> GetNeighborVertexes(const Graph &g);
  void ChooseNextVertex(const Graph::matrix_uint32_t m, std::vector<std::size_t> neighbors, std::vector<double> probability);
};

class AntColony {
public:
  using Matrix = std::vector<std::vector<double>>;
  AntColony(const Graph &graph);
  TsmResult SolveSalesmansProblem();

private:
  const double kAlpha_ = 1.0;
  const double kBeta_ = 2.0;
  const double kPheromone0_ = 1;
  const double kQ_ = 5.0;
  const double kEvaporation_ = 0.2;

  Graph graph_;
  Matrix pheromone_;
  std::vector<Ant> ants_;

  void CreateAnts();
  void UpdateGlobalPheromone(const Matrix &local_pheromone_update);
  bool CheckIsAllVertexes(std::vector<std::size_t> vertexes);
};

} // namespace s21

#endif // A2_SIMPLENAVIGATOR_v1_0_CPP_CORE_S21_ANT_COLONY_H_
