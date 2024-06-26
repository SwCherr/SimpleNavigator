#include "s21_ant_colony.h"
#include <cmath>
#include <random>

namespace s21 {
AntColonyOptimization::AntColonyOptimization(const Graph &graph)
        : kQ_(0.015 * pow(graph.GetSize(), 3)), graph_(graph) { // graph.getGraphWeight() -> graph.GetSize()^2
          
   const std::size_t size = graph_.GetSize();
   Matrix matrix(size, std::vector<double>(size));

   for (std::size_t row = 0; row != size; ++row)
      for (std::size_t col = 0; col != size; ++col)
        if (row != col) matrix[row][col] = kPheromone0_;

   pheromone_ = std::move(matrix);
}

void AntColonyOptimization::CreateAnts() {
  const auto kAntsCount = graph_.GetSize();
  ants_.resize(kAntsCount);

  for (std::size_t i = 0; i != kAntsCount; ++i)
    ants_[i] = Ant(i);
}

void AntColonyOptimization::UpdateGlobalPheromone(const Matrix &lpu) {
  // lpu - local pheromone update
  for (std::size_t from = 0, size = lpu.size(); from != size; ++from) {
    for (std::size_t to = 0; to != size; ++to) {
      pheromone_[from][to] = (1 - kEvaporation_) * pheromone_[from][to] + lpu[from][to];
      if (pheromone_[from][to] < 0.01 and from != to)
        pheromone_[from][to] = 0.01;
    }
  }
}

double Ant::getRandomChoice() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 9);
  return dist(gen) % 2 == 1;
}

std::vector<std::size_t> Ant::getNeighborVertexes(const Graph &graph) {
  std::vector<std::size_t> vertexes;
  Graph::matrix_uint32_t g = graph.GetMatrix();

  for (std::size_t to = 0; to != graph.GetSize(); ++to) {
    bool edge_is_exist = g[current_location][to] != 0;
    bool vertex_is_unvisited = std::find(visited.begin(), visited.end(), to) == visited.end();
    if (edge_is_exist and vertex_is_unvisited)
      vertexes.push_back(to);
  }
  return vertexes;   
}

void Ant::MakeChoice(const Graph &graph, const Matrix &p, double alpha, double beta) {
  Graph::matrix_uint32_t g = graph.GetMatrix();
  if (path.vertices.empty()) {
    path.vertices.push_back(current_location+1);
    visited.push_back(current_location);
  }

  std::vector<std::size_t> neighbor_vertexes = getNeighborVertexes(graph);

  if (neighbor_vertexes.empty()) {
    can_continue = false;
    if (g[current_location][start_location] != 0) {
      path.vertices.push_back(start_location+1);
      path.distance += g[current_location][start_location];
    }
    return;
  }

   std::vector<double> choosing_probability(neighbor_vertexes.size());

  {
    // Подсчет вероятности перехода муравья из одной вершины в другую
    std::vector<double> wish;
    std::vector<double> probability; 
    double summary_wish = 0.0f;
    for (auto v : neighbor_vertexes) {
      double t = p[current_location][v];
      double w = g[current_location][v];
      double n = 1 / w;
      wish.push_back(std::pow(t, alpha) * std::pow(n, beta));
      summary_wish += wish.back();
    }

    for (std::size_t neighbor = 0; neighbor != neighbor_vertexes.size(); ++neighbor) {
      probability.push_back(wish[neighbor] / summary_wish);
      if (neighbor == 0)
        choosing_probability[neighbor] = probability.back();
      else
        choosing_probability[neighbor] = choosing_probability[neighbor - 1] + probability.back();
    }
  }

  // Определение следующей вершины, которую посетит муравей
  std::size_t next_vertex = 0;
  double choose = getRandomChoice();

  for (std::size_t n = 0; n != neighbor_vertexes.size(); ++n ) {
    if (choose <= choosing_probability[n]) {
      next_vertex = neighbor_vertexes[n];
      break;
    }
  }

  path.vertices.push_back(next_vertex+1);
  path.distance += g[current_location][start_location];
  visited.push_back(next_vertex);
  current_location = next_vertex;
}

TsmResult AntColonyOptimization::SolveSalesmansProblem() {
  TsmResult path;
  if (graph_.GetSize() > 0) {

    constexpr std::size_t kMaxIterationsWithoutImprovement = 100;
    const std::size_t size = graph_.GetSize();
    std::size_t counter = 0;

    path.distance = INF;

    while (counter++ != kMaxIterationsWithoutImprovement) {
      Matrix local_pheromone_update(size, std::vector<double>(size, 0.0));
      CreateAnts();

      for (auto &ant : ants_) {
        while (ant.can_continue)
          ant.MakeChoice(graph_, pheromone_, kAlpha_, kBeta_);

        auto ant_path = ant.path;
        if (ant_path.vertices.size() >= size) {
          if (path.distance > ant.path.distance) {
            path = std::move(ant.path);
            counter = 0;
          }

          for (std::size_t v = 0; v != ant_path.vertices.size() - 1; ++v) {
            local_pheromone_update[ant_path.vertices[v]-1][ant_path.vertices[v + 1]-1] += kQ_ / ant_path.distance;
            // printf("%f ", ant_path.distance);
          }
          // printf("\n\n");
            
        }
  
        printf("ant_path = %f | ", ant.path.distance);
        printf("path = %f \n", path.distance);
        
      }
      UpdateGlobalPheromone(local_pheromone_update);
    }

    
  }
  return path;
}

} // namespace s21