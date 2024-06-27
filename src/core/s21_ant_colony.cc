#include "s21_ant_colony.h"

#include <algorithm>
#include <cmath>
#include <random>

namespace s21 {
AntColony::AntColony(const Graph &graph)
    : kQ_(0.015 * pow(graph.GetSize(), 2)), graph_(graph) {
  const std::size_t size = graph_.GetSize();
  Matrix matrix(size, std::vector<double>(size));
  for (std::size_t row = 0; row != size; row++) {
    for (std::size_t col = 0; col != size; col++) {
      if (row != col) {
        matrix[row][col] = kPheromone0_;
      }
    }
  }
  pheromone_ = std::move(matrix);
}

void AntColony::CreateAnts() {
  const size_t kAntsCount = graph_.GetSize();
  ants_.resize(kAntsCount);
  for (std::size_t i = 0; i != kAntsCount; i++) {
    ants_[i] = Ant(i);
  }
}

void AntColony::UpdateGlobalPheromone(const Matrix &lpu) {
  for (std::size_t from = 0, size = lpu.size(); from != size; from++) {
    for (std::size_t to = 0; to != size; to++) {
      pheromone_[from][to] =
          (1 - kEvaporation_) * pheromone_[from][to] + lpu[from][to];
      if (pheromone_[from][to] < 0.01 && from != to) {
        pheromone_[from][to] = 0.01;
      }
    }
  }
}

double Ant::GetRandomChoice() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 10);
  return (double)dist(gen) / 10;
}

std::vector<std::size_t> Ant::GetNeighborVertexes(const Graph &graph) {
  std::vector<std::size_t> vertexes;
  Graph::matrix_uint32_t g = graph.GetMatrix();
  for (std::size_t to = 0; to < graph.GetSize(); to++) {
    bool edge_is_exist = g[current_location][to] != 0;
    bool vertex_is_unvisited =
        std::find(visited.begin(), visited.end(), to) == visited.end();
    if (edge_is_exist && vertex_is_unvisited) vertexes.push_back(to);
  }
  return vertexes;
}

void Ant::MakeChoice(const Graph &graph, const Matrix &p, double alpha,
                     double beta) {
  Graph::matrix_uint32_t g = graph.GetMatrix();
  if (path.vertexes.empty()) {
    path.vertexes.push_back(current_location + 1);
    visited.push_back(current_location);
  }

  std::vector<std::size_t> neighbors = GetNeighborVertexes(graph);
  if (neighbors.empty()) {
    can_continue = false;
    if (g[current_location][start_location] != 0) {
      path.vertexes.push_back(start_location + 1);
      path.distance += g[current_location][start_location];
    }
  } else {
    std::vector<double> choose_probability(neighbors.size());
    std::vector<double> wish;
    std::vector<double> probability;
    double summary_wish = 0.0f;
    for (auto v : neighbors) {
      double t = p[current_location][v];
      double w = g[current_location][v];
      double n = 1 / w;
      wish.push_back(std::pow(t, alpha) * std::pow(n, beta));
      summary_wish += wish.back();
    }

    for (std::size_t neighbor = 0; neighbor != neighbors.size(); neighbor++) {
      probability.push_back(wish[neighbor] / summary_wish);
      if (neighbor == 0)
        choose_probability[neighbor] = probability.back();
      else
        choose_probability[neighbor] =
            choose_probability[neighbor - 1] + probability.back();
    }
    ChooseNextVertex(g, neighbors, choose_probability);
  }
}

void Ant::ChooseNextVertex(const Graph::matrix_uint32_t m,
                           std::vector<std::size_t> neighbors,
                           std::vector<double> probability) {
  bool is_choose = false;
  double choose = GetRandomChoice();
  std::size_t next_vertex = 0;

  for (std::size_t n = 0; n != neighbors.size(); n++) {
    if (choose <= probability[n]) {
      next_vertex = neighbors[n];
      is_choose = true;
      break;
    }
  }

  if (is_choose) {
    path.vertexes.push_back(next_vertex + 1);
    path.distance += m[current_location][next_vertex];
    visited.push_back(next_vertex);
    current_location = next_vertex;
  }
}

bool AntColony::CheckIsAllVertexes(std::vector<std::size_t> vertexes,
                                   std::size_t start_location) {
  bool is_all_vertexes = true;
  int start_vertex_count = 0;
  for (size_t i = 1; i <= vertexes.size(); i++) {
    bool is_vertex = false;
    for (size_t j = 0; j < vertexes.size(); j++) {
      if (vertexes[j] == i) {
        if (vertexes[j] == start_location) start_vertex_count++;
        is_vertex = true;
        continue;
      }
    }
    if (!is_vertex && start_vertex_count == 2) {
      is_all_vertexes = false;
      break;
    }
  }
  return is_all_vertexes;
}

TsmResult AntColony::SolveSalesmansProblem() {
  TsmResult path_res;
  std::size_t counter = 0;
  const std::size_t kMaxIterationsWithoutImprovement = 100;
  const std::size_t size = graph_.GetSize();

  if (graph_.GetSize() > 0) {
    path_res.distance = INF;
    while (counter++ < kMaxIterationsWithoutImprovement) {
      Matrix local_pheromone_update(size, std::vector<double>(size, 0.0));
      CreateAnts();

      for (auto &ant : ants_) {
        while (ant.can_continue)
          ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);
        auto path_ant = ant.path;
        // if (path_ant.vertexes.size() == size+1) {
        if (path_res.distance > path_ant.distance) {
          if (CheckIsAllVertexes(path_ant.vertexes, ant.start_location)) {
            path_res = std::move(ant.path);
            counter = 0;
          }
        }
        for (std::size_t v = 0; v != path_ant.vertexes.size() - 1; v++) {
          local_pheromone_update[path_ant.vertexes[v] - 1]
                                [path_ant.vertexes[v + 1] - 1] +=
              kQ_ / path_ant.distance;
        }
        // }
      }
      UpdateGlobalPheromone(local_pheromone_update);
    }
  }

  if (path_res.vertexes.size() < size) {
    path_res.vertexes.clear();
    path_res.distance = 0;
    fprintf(stderr, "usage: there is no solution to this graph\n");
  }
  return path_res;
}
}  // namespace s21
